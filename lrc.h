// Parse lrc file
#ifndef LRC_H
#define LRC_H

#include <QQmlEngine>
#include <QRegularExpression>

class LyricLine : public QObject {
    Q_OBJECT
    Q_PROPERTY(qint64 timestamp READ timestamp CONSTANT)
    Q_PROPERTY(QString sentence READ sentence CONSTANT)

public:
    explicit LyricLine(qint64 timestamp, QString sentence)
        : QObject(nullptr)
    {
        // QML Javascript might take over the ownership and garbage collect
        // this object since it doesn't have parent.
        // Here forbid it.
        QQmlEngine::setObjectOwnership(this, QQmlEngine::CppOwnership);
        m_timestamp = timestamp;
        m_sentence = sentence;
    }

    qint64 timestamp()
    {
        return m_timestamp;
    }

    QString sentence()
    {
        return m_sentence;
    }

public:
    qint64 m_timestamp;
    QString m_sentence;
};

// A struct records all required information in the lrc file
struct LrcContent {
    QList<LyricLine*> lyricLines;
    void clear();
};

LrcContent parse_lrc(QString lrc_text);

#endif // LRC_H
