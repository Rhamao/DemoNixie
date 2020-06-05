
#include <QtGui/QGuiApplication>
#include <QtQml/QQmlApplicationEngine>
#include <QtQml/QQmlContext>

#include "qmlapp.h"

void QmlApp::handleQmlDbgInit(DbgLink* obj)
{
    m_dbgLink = obj;
}

void QmlApp::testButton()
{
    m_dbgLink->appendLine("You Only Look Once");
}
