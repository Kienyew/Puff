// Backend and model for the lyrics view
#ifndef LYRICSVIEW_H
#define LYRICSVIEW_H

#include "lrc.h"
#include <QAbstractListModel>
#include <QObject>
#include <QQmlEngine>
#include <QQmlListProperty>

class LyricsModel : public QAbstractListModel {
    Q_OBJECT
    Q_PROPERTY(QUrl lyricSource READ lyricSource WRITE setLyricSource NOTIFY lyricSourceChanged)
public:
    enum LyricsViewRoles {
        SentenceRole = Qt::UserRole + 1,
        TimestampRole
    };
    LyricsModel(QObject* parent = nullptr);

    // Allows QML get the lyric line by index
    Q_INVOKABLE LyricLine getLyricLine(int index)
    {
        if (index >= 0 && index < lrc_content.lyricLines.count()) {
            return lrc_content.lyricLines[index];
        } else {
            return LyricLine();
        }
    }

    QUrl lyricSource()
    {
        return m_lyricSource;
    }

    void setLyricSource(QUrl lyricSource);

    virtual int rowCount(const QModelIndex& parent) const override;
    virtual QVariant data(const QModelIndex& index, int role) const override;

public slots:
    void loadLyricsFile(QUrl lyricSource);

signals:
    void lyricSourceChanged(QUrl lyricSource);

protected:
    virtual QHash<int, QByteArray> roleNames() const override;

private:
    QUrl m_lyricSource;
    LrcContent lrc_content;
};

#endif // LYRICSVIEW_H
