#include "lrc.h"
#include "lyricsmodel.h"
#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include <fstream>

int main(int argc, char* argv[])
{
    QGuiApplication app(argc, argv);
    QQmlApplicationEngine engine;
    qmlRegisterType<LyricsModel>("kienyew.github", 1, 0, "LyricsModel");
    engine.load("qrc:/Puff/main.qml");
    return app.exec();
}
