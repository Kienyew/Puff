#include "config.h"
#include "lrc.h"
#include "lyricsmodel.h"
#include <QDir>
#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include <QStandardPaths>
#include <fstream>

#define APP_NAME "puff"

QString configPath()
{
    QDir config_dir = QDir(QStandardPaths::writableLocation(QStandardPaths::ConfigLocation));
    config_dir.mkdir(APP_NAME);
    config_dir.cd(APP_NAME);
    return config_dir.filePath("config.json");
}

int main(int argc, char* argv[])
{
    QGuiApplication app(argc, argv);
    QQmlApplicationEngine engine;
    Config config(configPath());
    qmlRegisterType<LyricsModel>("kienyew.github", 1, 0, "LyricsModel");
    engine.rootContext()->setContextProperty("config", &config);
    engine.load("qrc:/Puff/main.qml");
    int exit_code = app.exec();
    config.write();
    return exit_code;
}
