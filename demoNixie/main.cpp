#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include "qmlapp.h"
#include "scrollableClock.h"

int main(int argc, char *argv[])
{
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
    TimeZone b(void);
    QGuiApplication app(argc, argv);
    QmlApp a;


    return app.exec();
}
