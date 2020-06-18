#include <QBluetoothDeviceDiscoveryAgent>
#include <QQmlEngine>
#include <QList>
#include <QBluetoothDeviceInfo>
#include "blewrapper.h"
#include <QByteArray>
#include <QColor>

BleWrapper::BleWrapper(QObject *parent) : QObject(parent)
{
    m_discoveryAgent = new QBluetoothDeviceDiscoveryAgent(this);
    QObject::connect(m_discoveryAgent, SIGNAL(deviceDiscovered(QBluetoothDeviceInfo)),
                this, SLOT(deviceDiscovered(QBluetoothDeviceInfo)));
    QObject::connect(m_discoveryAgent, SIGNAL(finished()),
                this, SLOT(stopDiscovery()));
//    QObject::connect(this, SIGNAL(connected()), this, SLOT(discoverService()));
    // not needed signal : deviceUpdated(const QBluetoothDeviceInfo &info, QBluetoothDeviceInfo::Fields updatedFields)
}

void BleWrapper::registerQml()
{
    qmlRegisterType<BleWrapper>("BleLink", 1, 0, "BleLink");
}

void BleWrapper::writeAnimation(bool animMode, QColor color0, uint32_t time0, QColor color1, uint32_t time1, QColor color2, uint32_t time2)
{
    if (m_animationFound)
    {
        int r0;
        int g0;
        int b0;
        int r1;
        int g1;
        int b1;
        int r2;
        int g2;
        int b2;
        color0.getRgb(&r0, &g0, &b0);
        color1.getRgb(&r1, &g1, &b1);
        color2.getRgb(&r2, &g2, &b2);
        char c[22] = {animMode,
                      (char)r0, (char)g0, (char)b0, (char)(time0 >> 24), (char)(time0 >> 16), (char)(time0 >> 8), (char)time0,
                      (char)r1, (char)g1, (char)b1, (char)(time1 >> 24), (char)(time1 >> 16), (char)(time1 >> 8), (char)time1,
                      (char)r2, (char)g2, (char)b2, (char)(time2 >> 24), (char)(time2 >> 16), (char)(time2 >> 8), (char)time2};
        QByteArray data = QByteArray(c,22);
        m_nixieService->writeCharacteristic(m_animCharac, data, QLowEnergyService::WriteWithoutResponse);
        emit debugSended(QString("Write Animation"));
    }
}

void BleWrapper::writeTime(quint8 hour, quint8 minute, quint8 second)
{
    if (m_timeFound)
    {
        char c[3] = {(char)hour, (char)minute, (char)second};
        QByteArray data = QByteArray(c,3);
        m_nixieService->writeCharacteristic(m_timeCharac, data, QLowEnergyService::WriteWithoutResponse);
        emit debugSended(QString("Write Time"));

    }
}

void BleWrapper::scanCharac()
{
    emit debugSended(QString("Scan characteristique ..."));
    QList<QLowEnergyCharacteristic>  characList = m_nixieService->characteristics();
    int i = 0;
    while (i < characList.count())
    {
        emit debugSended(QString("list animation ").append(QString::number(characList.at(i).uuid().toUInt16(),16)));

        if (characList.at(i).uuid().toUInt16() == m_reservedAnimCharac)
        {
            m_animCharac = characList.at(i);
            emit animCharacFounded();
            emit debugSended(QString("animation charac found "));
            m_animationFound = true;
        }
        else if (characList.at(i).uuid().toUInt16() == m_reservedTimeCharac)
        {
            m_timeCharac = characList.at(i);
            emit timeCharacFounded();
            emit debugSended(QString("time charac found "));
            m_timeFound = true;
        }
        i++;
    }
}

void BleWrapper::serviceError(QLowEnergyService::ServiceError error)
{
    if (error == QLowEnergyService::ServiceError::NoError)
        emit debugSended(QString("Service -> No error occured"));
    else if (error == QLowEnergyService::ServiceError::OperationError)
        emit debugSended(QString("Service -> An operation was attempted while service was not ready"));
    else if (error == QLowEnergyService::ServiceError::CharacteristicReadError)
        emit debugSended(QString("Service -> An attempt to read a characteristic value failed."));
    else if (error == QLowEnergyService::ServiceError::CharacteristicWriteError)
        emit debugSended(QString("Service -> An attempt to write a new value to a characteristic failed"));
    else if (error == QLowEnergyService::ServiceError::DescriptorReadError)
        emit debugSended(QString("Service -> An attempt to read a descriptor value failed"));
    else if (error == QLowEnergyService::ServiceError::DescriptorWriteError)
        emit debugSended(QString("Service -> An attempt to write a new value to a descriptor failed"));
    else if (error == QLowEnergyService::ServiceError::UnknownError)
        emit debugSended(QString("Service -> An unknown error occurred when interacting with the service"));
}

void BleWrapper::characteristicWritten(const QLowEnergyCharacteristic &characteristic, const QByteArray &newValue)
{
    emit debugSended(QString("characteristique ").append(QString::number(characteristic.uuid().toUInt16(),16)).append(" writen"));
}

void BleWrapper::serviceStateChanged(QLowEnergyService::ServiceState state)
{
    if (state == QLowEnergyService::ServiceState::ServiceDiscovered)
    {
        scanCharac();
    }
    else if (state == QLowEnergyService::ServiceState::DiscoveringServices)
    {
        emit debugSended(QString("Service discovering ..."));
    }
}

void BleWrapper::serviceDiscovered(const QBluetoothUuid &newService)
{
    if (newService.toUInt16() == m_reservedBleService)
    {
        m_nixieService = m_controller->createServiceObject(newService, this);
        connect(m_nixieService, SIGNAL(stateChanged(QLowEnergyService::ServiceState)), this, SLOT(serviceStateChanged(QLowEnergyService::ServiceState)));
        connect(m_nixieService, SIGNAL(error(QLowEnergyService::ServiceError)), this, SLOT(serviceError(QLowEnergyService::ServiceError)));
        connect(m_nixieService, SIGNAL(characteristicWritten(const QLowEnergyCharacteristic, const QByteArray)), this, SLOT(characteristicWritten(const QLowEnergyCharacteristic, const QByteArray)));
        m_nixieService->discoverDetails();

    }

    int i = 0;
    while (i < m_serviceList.count())
    {
        if (m_serviceList.at(i) == newService)
        {
            return;
        }
        i++;
    }
    m_serviceList.append(newService);
    emit serviceFounded(newService);
}

void BleWrapper::deviceDiscovered(const QBluetoothDeviceInfo &device)
{
//        qDebug() << "Found new device:" << device.name() << '(' << device.address().toString() << ')';
    if (m_autoConnect)
    {
        if (device.address().toString().contains(m_reservedBleAddr,Qt::CaseInsensitive))
        {
            createCentral(device);
        }
    }

    int i = 0;
    while (i<m_devinfoList.count())
    {
        if (m_devinfoList.at(i).address() == device.address())
        {
            return;
        }
        i++;
    }
    m_devinfoList.append(device);
    emit deviceFounded(device);
}

void BleWrapper::runDiscovery()
{
    m_discoveryAgent->start(QBluetoothDeviceDiscoveryAgent::LowEnergyMethod);
    emit discoveryChanged();
    emit debugSended(QString("discovery Started"));
}

void BleWrapper::stopDiscovery()
{
    m_discoveryAgent->stop();
    emit discoveryChanged();
    emit debugSended(QString("Discovery Stopped"));
}

void BleWrapper::createCentral(QBluetoothDeviceInfo device)
{
    m_controller = QLowEnergyController::createCentral(device);
    if (discovery())
        stopDiscovery();
    emit debugSended(QString("Controller Created"));
    connect(m_controller, SIGNAL(connected()), this, SLOT(connectionValidate()));
    connect(m_controller, SIGNAL(stateChanged(QLowEnergyController::ControllerState )), this, SLOT(updateWrapperState(QLowEnergyController::ControllerState)));

    m_controller->connectToDevice();
}

void BleWrapper::setAutoCreate(bool enable, QString str)
{
    m_autoConnect = enable;
    m_reservedBleAddr = str;
}

void BleWrapper::setConnected(bool enable)
{
    m_isConnected = enable;
    emit connectedChanged();
}

void BleWrapper::updateWrapperState(QLowEnergyController::ControllerState state)
{
    if (state == QLowEnergyController::ControllerState::ConnectedState)
        m_isConnected = 1;
    else
        m_isConnected = 0;
}


void BleWrapper::connectionValidate()
{
    setConnected(true);
    connect(m_controller, SIGNAL(serviceDiscovered(const QBluetoothUuid &)), this, SLOT(serviceDiscovered(const QBluetoothUuid &)));

    m_controller->discoverServices();
    emit connected();
    emit debugSended(QString("connected"));
}
