#include "dbglink.h"
#include <QQmlEngine>
DbgLink::DbgLink(QObject *parent) : QObject(parent)
{

}

void DbgLink::registerQml()
{
    qmlRegisterType<DbgLink>("DbgLink", 1, 0, "DbgLink");
}

void DbgLink::setText(QString str)
{
    if (!m_text.compare(str))
    {
        m_text = str;
        emit textChanged();
    }
}

void DbgLink::append(QString str)
{
    m_text.append(str);
    emit textChanged();
}

void DbgLink::appendLine(QString str)
{
    m_text.append(str).append("<br>");
    emit textChanged();
}

void DbgLink::appendColoredLine(QString str, QString color)
{
    m_text.append("<font color=\"").append(color).append("\">").append(str).append("</font><br>");
    emit textChanged();
}

void DbgLink::clear()
{
    m_text.clear();
    emit textChanged();
}
#if defined (Q_OS_ANDROID)
void DbgLink::showToast(const QString &message, Duration duration) {
    // all the magic must happen on Android UI thread

    QtAndroid::runOnAndroidThread([message, duration] {
        QAndroidJniObject javaString = QAndroidJniObject::fromString(message);
        QAndroidJniObject toast = QAndroidJniObject::callStaticObjectMethod("android/widget/Toast", "makeText",
                                                                            "(Landroid/content/Context;Ljava/lang/CharSequence;I)Landroid/widget/Toast;",
                                                                            QtAndroid::androidActivity().object(),
                                                                            javaString.object(),
                                                                            jint(duration));
        toast.callMethod<void>("show");
    });
}
#endif
