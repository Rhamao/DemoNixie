#ifndef QMLAPP_H
#define QMLAPP_H


#include <QtCore/QObject>
#include <QtGui/QGuiApplication>
#include <QtQuick/QQuickView>
#include <QtQml/QQmlApplicationEngine>
#include <QtQml/QQmlContext>

#include "dbglink.h"


#define V_MAIN      1 //  id des views
#define V_DBG       2 //  id des views



class QmlApp : public QQuickView
{
    Q_OBJECT

public:
    explicit  QmlApp(QWindow *parent = nullptr);
    bool event(QEvent *event) override;
    ~QmlApp() override;


signals:

public slots:
    void    handleQmlDbgInit(DbgLink *dbg);
    void    testButton();
private slots:
    void    viewChanger(int id);
    void    loadMain();
    void    loadDbg();


private:
    int m_pageId;
    DbgLink *m_dbgLink = nullptr;

};

#endif // QMLAPP_H
