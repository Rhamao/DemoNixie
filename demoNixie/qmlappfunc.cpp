
#include <QtGui/QGuiApplication>
#include <QtQml/QQmlApplicationEngine>
#include <QtQml/QQmlContext>

#include "qmlapp.h"

void QmlApp::handleTimeZoneInit(QObject *obj)
{
    clock = (TimeZone*) obj;
}
void QmlApp::handleQmlDbgInit(DbgLink* obj)
{
    m_dbgLink = obj;
}

void QmlApp::handleQmlBleInit(BleWrapper* ble)
{
    m_bleWrapper = ble;
    connect(m_bleWrapper, SIGNAL(deviceFounded(const QBluetoothDeviceInfo&)), this, SLOT(getBleDevice(const QBluetoothDeviceInfo&)));
    connect(m_bleWrapper, SIGNAL(serviceFounded(const QBluetoothUuid&)), this, SLOT(getBleService(const QBluetoothUuid&)));
    connect(m_bleWrapper, SIGNAL(debugSended(QString)), m_dbgLink, SLOT(appendLine(QString)));
    m_bleWrapper->setAutoCreate(true, "00:A0:50:00");
}

void QmlApp::testButton()
{
    m_dbgLink->appendLine("You Only Look Once");
}

void QmlApp::getBleDevice(const QBluetoothDeviceInfo &device)
{
    if (m_dbgLink)
    {
        m_dbgLink->appendColoredLine(QString("Found new device : ").append(device.name()).append('(').append(device.address().toString()).append(')'), "blue");
    }
    else
    {
        qDebug() << "Found new device : " << device.name() << '(' << device.address().toString() << ')';
    }
}

void QmlApp::getBleService(const QBluetoothUuid &service)
{
    if (m_dbgLink)
    {
        m_dbgLink->appendColoredLine(QString("Found new Service : ").append(QString::number(service.toUInt16())), "cornflowerblue");
    }
    else
    {
        qDebug() << QString("Found new Service :").append(QString::number(service.toUInt16()));
    }
}
