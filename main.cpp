#include <QApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include <QQmlComponent>
#include "axedroid.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    //temp fix for text rendering issues
    qputenv("QML_USE_GLYPHCACHE_WORKAROUND", QByteArray("1"));

    AxeDroid axedroid;

    QQmlApplicationEngine engine;
    engine.rootContext()->setContextProperty("axedroid", &axedroid);
    engine.load(QUrl(QStringLiteral("qrc:///main.qml")));

    return app.exec();
}
