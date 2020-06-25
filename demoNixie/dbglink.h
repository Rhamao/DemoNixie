#ifndef DBGLINK_H
#define DBGLINK_H

#include <QObject>
#if defined (Q_OS_ANDROID)
#include <QtAndroidExtras>
#endif

class DbgLink : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString text READ text WRITE setText NOTIFY textChanged)
    Q_PROPERTY(QString new_text READ new_text WRITE setNew_text NOTIFY newText)

public:
    explicit DbgLink(QObject *parent = nullptr);
    static void registerQml();


    QString text() const { return m_text; }
    void setText(QString str);
    enum Duration {
        SHORT = 0,
        LONG = 1
    };
    QString new_text() const;
    void setNew_text(const QString &new_text);

public slots:
    void append(QString str);
    void appendLine(QString str);
    void appendColoredLine(QString str, QString color);
    void clear();
    #if defined (Q_OS_ANDROID)
    void showToast(const QString &message, Duration duration = LONG);
    #else
    void showToast(const QString &message, Duration duration = LONG);
    #endif

signals:
    void textChanged();
    void newText();

private:
    QString m_text;
    QString m_new_text;


};

#endif // DBGLINK_H
