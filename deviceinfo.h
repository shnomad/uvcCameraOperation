#ifndef DEVICEINFO_H
#define DEVICEINFO_H

#include <QObject>
#include <QFile>
#include <QNetworkInterface>

class deviceInfo : public QObject
{
    Q_OBJECT
public:
    explicit deviceInfo(QObject *parent = nullptr);
    ~deviceInfo();

    QString get_ClientID();
    QString get_BrokerIP();
    QString get_ServerPort();

signals:

public slots:
};

#endif // DEVICEINFO_H
