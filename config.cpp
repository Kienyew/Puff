#include "config.h"

void Config::load()
{
    QFile file(config_file);
    if (!file.open(QIODevice::ReadOnly)) {
        qWarning("Could not open config file.");
        return;
    }

    QByteArray json_content = file.readAll();
    QJsonDocument json = QJsonDocument::fromJson(json_content);
    QJsonObject object = json.object();

    this->m_recentAudioFile = QUrl::fromLocalFile(object["audio_file"].toString());
    this->m_recentLrcFile = QUrl::fromLocalFile(object["lrc_file"].toString());
}

void Config::write()
{
    QFile file(config_file);
    if (!file.open(QIODevice::WriteOnly)) {
        qWarning("Could not open config file.");
        return;
    }

    QJsonDocument document(this->toJsonObject());
    QByteArray json_content = document.toJson();
    file.write(json_content);
}

QJsonObject Config::toJsonObject()
{
    QJsonObject object;
    object["audio_file"] = this->m_recentAudioFile.toLocalFile();
    object["lrc_file"] = this->m_recentLrcFile.toLocalFile();
    return object;
}

const QUrl& Config::recentLrcFile() const
{
    return m_recentLrcFile;
}

void Config::setRecentLrcFile(const QUrl& newRecentLrcFile)
{
    if (m_recentLrcFile == newRecentLrcFile)
        return;
    m_recentLrcFile = newRecentLrcFile;
    emit recentLrcFileChanged();
}

const QUrl& Config::recentAudioFile() const
{
    return m_recentAudioFile;
}

void Config::setRecentAudioFile(const QUrl& newRecentAudioFile)
{
    if (m_recentAudioFile == newRecentAudioFile)
        return;
    m_recentAudioFile = newRecentAudioFile;
    emit recentAudioFileChanged();
}
