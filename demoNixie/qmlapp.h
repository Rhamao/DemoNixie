#ifndef QMLAPP_H
#define QMLAPP_H


#include <QtCore/QObject>
#include <QtGui/QGuiApplication>
#include <QtQuick/QQuickView>
#include <QtQml/QQmlApplicationEngine>
#include <QtQml/QQmlContext>

#include "scrollableClock.h"



#define V_MAIN      1 //  id des views



class QmlApp : public QQuickView
{
    Q_OBJECT

public:
    explicit  QmlApp(QWindow *parent = nullptr);
    bool event(QEvent *event) override;
    ~QmlApp() override;


signals:

public slots:
//    void    handleChecker(int val);
    void handleTimeZoneInit(QObject *obj);
private slots:
    void    viewChanger(int id);
    void    loadMain();


private:
    int m_pageId;
    TimeZone *clock;
};

#endif // QMLAPP_H
