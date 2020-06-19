#ifndef CLOCK_H
#define CLOCK_H

#include <QObject>
#include <QTimeZone>
#include <QDate>
#include <QDebug>

class TimeZone : public QObject
{
    Q_OBJECT
    Q_PROPERTY(uint timeZone READ getTimeZone WRITE setTimeZone NOTIFY timeZoneChanged)
public:
    explicit TimeZone();
    unsigned int getTimeZone() const;
    void setTimeZone(unsigned int value);
    static void registerQLM();

signals:
    void timeZoneChanged();

private:
    uint m_timeZone;
};

#endif // CLOCK_H
