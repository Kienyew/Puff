#include "lyricsmodel.h"
#include "lrc.h"
#include <QDebug>
#include <QFile>
#include <QObject>
#include <QQmlListProperty>

QHash<int, QByteArray> LyricsModel::roleNames() const
{
    QHash<int, QByteArray> roles;
    roles[SentenceRole] = "sentence";
    roles[TimestampRole] = "timestamp";
    return roles;
}

LyricsModel::LyricsModel(QObject* parent)
    : QAbstractListModel(parent)
{
    connect(this, &LyricsModel::lyricSourceChanged, this, &LyricsModel::loadLyricsFile);
}

void LyricsModel::setLyricSource(QUrl lyricSource)
{
    m_lyricSource = lyricSource;
    emit lyricSourceChanged(lyricSource);
}

int LyricsModel::rowCount(const QModelIndex& parent) const
{
    return lrc_content.lyricLines.count();
}

QVariant LyricsModel::data(const QModelIndex& index, int role) const
{
    int row = index.row();
    if (row < 0 || row >= lrc_content.lyricLines.count()) {
        return QVariant();
    }

    LyricLine lyricLine = lrc_content.lyricLines.at(row);
    switch (role) {
    case SentenceRole:
        return lyricLine.sentence;
    case TimestampRole:
        return lyricLine.timestamp;
    default:
        return QVariant();
    }
}

void LyricsModel::loadLyricsFile(QUrl lyricSource)
{
    QFile file = lyricSource.toLocalFile();
    if (!file.exists()) {
        qWarning() << "lyric source file does not exist: " << lyricSource;
        return;
    }

    if (file.open(QIODevice::ReadOnly)) {
        QTextStream stream(&file);
        QString text = stream.readAll();
        beginResetModel();
        lrc_content.clear();
        lrc_content = parse_lrc(text);
        endResetModel();
    } else {
        qWarning() << "Cannot read lyric source file: " << lyricSource;
        return;
    }
}
