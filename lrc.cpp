#include "lrc.h"

LrcContent parse_lrc(QString lrc_text)
{
    static const QRegularExpression lrc_line_pattern("\\[([0-5]?\\d):([0-5]?\\d)\\.(\\d+)?\\]+(.*)");
    LrcContent lrc_content;
    for (const QString& line : lrc_text.split("\n")) {
        QRegularExpressionMatch match = lrc_line_pattern.match(line.trimmed());
        if (!match.hasMatch()) {
            continue;
        }

        QString minutes = match.captured(1);
        QString seconds = match.captured(2);
        QString milliseconds = match.captured(3);
        qint64 timestamp = minutes.toInt() * 60000 + seconds.toInt() * 1000 + milliseconds.toInt();
        QString sentence = match.captured(4);
        LyricLine lyric_line { timestamp, sentence };
        lrc_content.lyricLines.append(lyric_line);
    }

    return lrc_content;
}

void LrcContent::clear()
{
    lyricLines.clear();
}
