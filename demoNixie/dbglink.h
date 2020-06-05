#ifndef DBGLINK_H
#define DBGLINK_H

#include <QObject>

class DbgLink : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString text READ text WRITE setText NOTIFY textChanged)

public:
    explicit DbgLink(QObject *parent = nullptr);
    static void registerQml();


    QString text() const { return m_text; }
    void setText(QString str);

public slots:
    void append(QString str);
    void appendLine(QString str);
    void appendColoredLine(QString str, QString color);
    void clear();

signals:
    void textChanged();

private:
    QString m_text;

};

#endif // DBGLINK_H
