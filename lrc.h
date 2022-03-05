// Parse lrc file
#ifndef LRC_H
#define LRC_H

#include <QQmlEngine>
#include <QRegularExpression>

// A struct store information of a lyric line
struct LyricLine {
    // Q_GADGET allows direct access of fields (sentence and timestamp) from QML
    Q_GADGET
    Q_PROPERTY(QString sentence MEMBER sentence)
    Q_PROPERTY(qint64 timestamp MEMBER timestamp)

public:
    qint64 timestamp;
    QString sentence;
};

// A struct records all required information in the lrc file
struct LrcContent {
    QList<LyricLine> lyricLines;
    void clear();
};

LrcContent parse_lrc(QString lrc_text);

#endif // LRC_H
