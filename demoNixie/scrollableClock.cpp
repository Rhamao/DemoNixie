#include "scrollableClock.h"
#include <QtQml/QQmlApplicationEngine>

TimeZone::TimeZone()
{
   // timeZone = qtimeZone.offsetFromUtc();
    QDateTime local(QDateTime::currentDateTime());
    QDateTime UTC(local.toUTC());
    QDateTime dt(UTC.date(), UTC.time(), Qt::LocalTime);
    qDebug() << "Local time is:" << local;
    qDebug() << "UTC time is:" << UTC;
    qDebug() << "No difference between times:" << local.secsTo(UTC);
    qDebug() << "Here is the difference between times:" << local.secsTo(dt);
    qDebug() << "Here is the difference between times:" << dt.secsTo(local);
    m_timeZone = dt.secsTo(local)/3600;
    qDebug() << "Here is the UTC:" << m_timeZone;
}

unsigned int TimeZone::getTimeZone() const
{
    return m_timeZone;
}

void TimeZone::setTimeZone(unsigned int value)
{
    m_timeZone = value;
    emit timeZoneChanged();
}

void TimeZone::registerQLM()
{
    qmlRegisterType<TimeZone>("TimeZone", 1, 0, "TimeZone");
}
