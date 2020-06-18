
#include <QtGui/QGuiApplication>
#include <QtQml/QQmlApplicationEngine>
#include <QtQml/QQmlContext>

#include "qmlapp.h"
#include "dbglink.h"
#include "blewrapper.h"

QmlApp::QmlApp(QWindow *parent) : QQuickView(parent)
{
    setResizeMode(QQuickView::SizeRootObjectToView);
    DbgLink::registerQml();
    BleWrapper::registerQml();
    rootContext()->setContextProperty("cpp", this); // uncomment this line to use c++ public slot function from QML
    setGeometry(50,50,680,800);
    viewChanger(V_DBG);
    show();
}


/*
 * Gestion Close Event
 */
bool QmlApp::event(QEvent *event)
{
    return QQuickView::event(event);
    if (event->type() == QEvent::Close)
    {
        if (m_pageId != V_MAIN)
        {
            viewChanger(V_MAIN);
            return true;
        }
    }
    return QQuickView::event(event);
}

QmlApp::~QmlApp()
{

}
