#include "deviceinfo.h"
#include "common.h"

deviceInfo::deviceInfo(QObject *parent) : QObject(parent)
{

}

deviceInfo::~deviceInfo()
{

}

QString deviceInfo::get_ClientID()
{
//    QString filename = "/boot/config.txt";
    QString filename = "/home/linaro/config.txt";

    QFile file(filename);

    if(!file.open(QFile::ReadOnly))
    {
       Log() << " Could not open the file for reading";
    }

    QTextStream in(&file);

    const QString config = in.readAll();

    QString device_name = config.section("#",-2,-2);

    file.close();

    return device_name.simplified();
}

QString deviceInfo::get_BrokerIP()
{
//  QString filename = "/boot/config.txt";
    QString filename = "/home/linaro/config.txt";

    QFile file(filename);

    if(!file.open(QFile::ReadOnly))
    {
       Log() << " Could not open the file for reading";
    }

    QTextStream in(&file);

    const QString config = in.readAll();

    QString broker_ip = config.section("#",-3,-3);

    file.close();

    return broker_ip.simplified();
}

QString deviceInfo::get_ServerPort()
{
//    QString filename = "/boot/config.txt";
    QString filename = "/home/linaro/config.txt";

    QFile file(filename);

    if(!file.open(QFile::ReadOnly))
    {
       Log() << " Could not open the file for reading";
    }

    QTextStream in(&file);

    const QString config = in.readAll();

    QString broker_ip = config.section("#",-1,-1);

    file.close();

    return broker_ip.simplified();
}
