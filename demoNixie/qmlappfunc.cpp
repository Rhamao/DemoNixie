
#include <QtGui/QGuiApplication>
#include <QtQml/QQmlApplicationEngine>
#include <QtQml/QQmlContext>

#include "qmlapp.h"

void QmlApp::handleTimeZoneInit(QObject *obj)
{
    clock = (TimeZone*) obj;
}
