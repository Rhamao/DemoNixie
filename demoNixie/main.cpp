#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include "qmlapp.h"
#include "scrollableClock.h"

#if defined (Q_OS_ANDROID)
// from https://forum.qt.io/topic/94795/how-to-request-the-permissions-in-runtime/9
#include <QtAndroidExtras/QtAndroidExtras>
const QVector<QString> permissions({"android.permission.ACCESS_COARSE_LOCATION",
                                    "android.permission.BLUETOOTH",
                                    "android.permission.BLUETOOTH_ADMIN"});
#endif

int main(int argc, char *argv[])
{
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
    TimeZone b(void);
    QGuiApplication app(argc, argv);

#if defined (Q_OS_ANDROID)
    //Request requiered permissions at runtime
    for(const QString &permission : permissions){
        auto result = QtAndroid::checkPermission(permission);
        if(result == QtAndroid::PermissionResult::Denied){
            auto resultHash = QtAndroid::requestPermissionsSync(QStringList({permission}));
            if(resultHash[permission] == QtAndroid::PermissionResult::Denied)
                return 0;
        }
    }
#endif

    QmlApp a;


    return app.exec();
}
