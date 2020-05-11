
#include <QtGui/QGuiApplication>
#include <QtQml/QQmlApplicationEngine>
#include <QtQml/QQmlContext>

#include "qmlapp.h"


void    QmlApp::viewChanger(int pageId)
{
    if (pageId == V_MAIN)
        QMetaObject::invokeMethod(this, "loadMain", Qt::QueuedConnection);
}


void    QmlApp::loadMain()
{
    setSource(QUrl("qrc:/main.qml"));
    m_pageId = V_MAIN;

}
