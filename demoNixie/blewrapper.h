#ifndef BLEWRAPPER_H
#define BLEWRAPPER_H

#include <QObject>
#include <QBluetoothDeviceDiscoveryAgent>
#include <QBluetoothDeviceInfo>
#include <QList>
#include <QLowEnergyController>
#include <QLowEnergyService>
#include <QColor>

class BleWrapper : public QObject
{
    Q_OBJECT
    Q_PROPERTY(bool connected READ connected WRITE setConnected NOTIFY connectedChanged)
    Q_PROPERTY(bool discovery READ discovery NOTIFY discoveryChanged)


public:
    explicit BleWrapper(QObject *parent = nullptr);
    static void registerQml();
    void setAutoCreate(bool enable, QString str = "");

    bool connected(){return m_isConnected;}
    void setConnected(bool enable);

public slots:
    // discovery
    bool discovery(){return m_discoveryAgent->isActive();}
    void runDiscovery();
    void createCentral(QBluetoothDeviceInfo device);
    void stopDiscovery();

    // controller
    void connectionValidate();

    // service
    void writeAnimation(bool animMode = false,
                        QColor color0 = Qt::white, uint32_t time0 = 0,
                        QColor color1 = Qt::white, uint32_t time1 = 0,
                        QColor color2 = Qt::white, uint32_t time2 = 0);
    void writeTime(quint8 hour = 0, quint8 minute = 0, quint8 second = 0);

signals:
    // discovery
    void discoveryChanged();
    void deviceFounded(const QBluetoothDeviceInfo &device);
    void debugSended(QString str);

    // controller
    void connectedChanged();
    void serviceFounded(const QBluetoothUuid &newService);

    void animCharacFounded();
    void timeCharacFounded();


private slots:
    void deviceDiscovered(const QBluetoothDeviceInfo &device);

    // controller
    void updateWrapperState(QLowEnergyController::ControllerState state);
    void serviceDiscovered(const QBluetoothUuid &newService);

    // service
    void serviceStateChanged(QLowEnergyService::ServiceState state);
    void scanCharac();
    void serviceError(QLowEnergyService::ServiceError error);

    // characteristique
    void characteristicWritten(const QLowEnergyCharacteristic &characteristic, const QByteArray &newValue);

private:
    QBluetoothDeviceDiscoveryAgent  *m_discoveryAgent;
    QList<QBluetoothDeviceInfo>     m_devinfoList;
    QList<QBluetoothUuid>           m_serviceList;

    QString                         m_reservedBleAddr = "";
    quint16                         m_reservedBleService = 0x2B4E ;

    quint16                         m_reservedAnimCharac = 0xDB56 ;
    quint16                         m_reservedTimeCharac = 0x7AF3 ;

    QLowEnergyController            *m_controller = nullptr;
    QLowEnergyService               *m_nixieService = nullptr;
    QLowEnergyCharacteristic        m_timeCharac;
    QLowEnergyCharacteristic        m_animCharac;
    bool                            m_animationFound = false;
    bool                            m_timeFound = false;

    bool                            m_autoConnect = false;

    // controller
    bool m_isConnected = false;

};

#endif // BLEWRAPPER_H
