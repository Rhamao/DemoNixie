
#include <QtGui/QGuiApplication>
#include <QtQml/QQmlApplicationEngine>
#include <QtQml/QQmlContext>

#include "qmlapp.h"


QmlApp::QmlApp(QWindow *parent) : QQuickView(parent)
{
    setResizeMode(QQuickView::SizeRootObjectToView);
    // rootContext()->setContextProperty("cpp", this); // uncomment this line to use c++ public slot function from QML
    setGeometry(50,50,680,800);
    viewChanger(V_MAIN);
    show();
}


/*
 * Gestion Close Event
 */
bool QmlApp::event(QEvent *event)
{
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
