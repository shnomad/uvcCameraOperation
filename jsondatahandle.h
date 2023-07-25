#ifndef JSONDATAHANDLE_H
#define JSONDATAHANDLE_H

#include <QObject>
#include <QFile>
#include <QMutex>
#include <QJsonDocument>
#include <QJsonParseError>
#include <QJsonObject>
#include <QJsonValue>
#include <QJsonArray>
#include "sys_cmd_resp.h"

class JsonDataHandle : public QObject
{
    Q_OBJECT

     static const QString filename;

public:
    explicit JsonDataHandle(QObject *parent = nullptr);    
    ~JsonDataHandle();

     QString encode_resp(QString, sys_cmd_resp *);
     sys_cmd_resp* cmd_parsing(QString);

     sys_cmd_resp *cmd_from_host;

signals:     
     void sig_comm_status(sys_cmd_resp *);

public slots:
};

#endif // JSONDATAHANDLE_H
