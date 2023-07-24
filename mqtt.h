#ifndef MQTT_H
#define MQTT_H

#include <QObject>
#include <QMqttClient>
#include <QTimer>
#include "deviceinfo.h"
#include "jsondatahandle.h"
#include "sys_cmd_resp.h"

class mqtt : public QObject
{
    Q_OBJECT
public:
    explicit mqtt(QObject *parent = nullptr);
    ~mqtt();

signals:
    void sig_read_from_socket(const QByteArray &data);
    void sig_doconnect();
    void sig_cmd_from_mqtt_to_camera(sys_cmd_resp *);

public slots:
    void setClientPort(int p);
    void ConnectBroker();
    void DisConnectBroker();
    void updateLogStateChange();

    void brokerDisconnected();
    void brokerConnected();

    bool Publish(QString, QString, quint8, bool);
    bool Subscribe(QString);
    bool pub_status_topic();
    bool pub_response_topic();
//  bool pub_response_topic(QString);
    bool sub_host_cmd_topic();

private:
     QMqttClient *m_client;

     QString client_id;
     QString pub_topic_status ="usbCam/connected/";
     QString pub_topic_resp ="usbCam/resp/";
     QString sub_topic_cmd ="usbCam/cmd/";

     QTimer *connect_broker_timer, *pub_topic_status_timer, *pub_topic_resp_timer, *sub_topic_cmd_timer;

     /* Coding channel control parameter */
//   Coding_Channel_Ctl mqtt_coding_ch_ctl{}, mqtt_coding_ch_ctl_tmp{};     
/*
     QString get_device_name();
     QString get_broker_ip();
*/
     deviceInfo m_device_info;
     QString getLocalInfo();
     sys_cmd_resp *m_cmd_mqtt, *m_resp_from_camserver;
     JsonDataHandle *json_to_cmd;
};

#endif // MQTT_H
