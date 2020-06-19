#ifndef QMLAPP_H
#define QMLAPP_H


#include <QtCore/QObject>
#include <QtGui/QGuiApplication>
#include <QtQuick/QQuickView>
#include <QtQml/QQmlApplicationEngine>
#include <QtQml/QQmlContext>

#include "scrollableClock.h"
#include "dbglink.h"
#include "blewrapper.h"


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
//    void    handleChecker(int val);
    void handleTimeZoneInit(QObject *obj);
    void    handleQmlDbgInit(DbgLink *dbg);
    void    handleQmlBleInit(BleWrapper *ble);
    void    testButton();
private slots:
    void    viewChanger(int id);
    void    loadMain();
    void    loadDbg();


    // BLE part
    void getBleDevice(const QBluetoothDeviceInfo &device);
    void getBleService(const QBluetoothUuid &service);


private:
    int m_pageId;
    TimeZone *clock;
    BleWrapper *m_bleWrapper = nullptr;
    DbgLink *m_dbgLink = nullptr;
};

#endif // QMLAPP_H
