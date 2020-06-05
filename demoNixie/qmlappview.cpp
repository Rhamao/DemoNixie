
#include <QtGui/QGuiApplication>
#include <QtQml/QQmlApplicationEngine>
#include <QtQml/QQmlContext>

#include "qmlapp.h"


void    QmlApp::viewChanger(int pageId)
{
    if (pageId == V_MAIN)
        QMetaObject::invokeMethod(this, "loadMain", Qt::QueuedConnection);
    else if (pageId == V_DBG)
        QMetaObject::invokeMethod(this, "loadDbg", Qt::QueuedConnection);
}


void    QmlApp::loadMain()
{
    setSource(QUrl("qrc:/main.qml"));
    m_pageId = V_MAIN;

}
void    QmlApp::loadDbg()
{
    setSource(QUrl("qrc:/DebugView.qml"));
    m_pageId = V_DBG;

}
