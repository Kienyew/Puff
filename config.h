#include <QFile>
#include <QJsonDocument>
#include <QJsonObject>
#include <QObject>

class Config : public QObject {
    Q_OBJECT
public:
    Config(const QString& config_file)
        : config_file(config_file)
    {
        load();
    }

    void load();
    void write();

private:
    QJsonObject toJsonObject();

public:
    const QUrl& recentLrcFile() const;
    void setRecentLrcFile(const QUrl& newRecentLrcFile);

    const QUrl& recentAudioFile() const;
    void setRecentAudioFile(const QUrl& newRecentAudioFile);

signals:
    void recentLrcFileChanged();
    void recentAudioFileChanged();

private:
    QString config_file;
    QUrl m_recentAudioFile;
    QUrl m_recentLrcFile;
    Q_PROPERTY(QUrl recentLrcFile READ recentLrcFile WRITE setRecentLrcFile NOTIFY recentLrcFileChanged)
    Q_PROPERTY(QUrl recentAudioFile READ recentAudioFile WRITE setRecentAudioFile NOTIFY recentAudioFileChanged)
};
