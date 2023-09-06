#include "mqtt.h"
#include "common.h"
//#include <QFile>
//#include <QNetworkInterface>

mqtt::mqtt(QObject *parent) : QObject(parent)
{
       json_to_cmd = new JsonDataHandle;
       m_cmd_mqtt = new sys_cmd_resp;
       m_resp_from_camserver = new sys_cmd_resp;       

//     client_id = get_device_name();
//     QString hostname = get_broker_ip();
       client_id = m_device_info.get_ClientID();
       QString hostname = m_device_info.get_BrokerIP();
       quint16 portnumber = 1883;

       m_client = new QMqttClient(this);
       m_client->setHostname(hostname);
       m_client->setPort(portnumber);
       m_client->setClientId(client_id);
       m_client->setKeepAlive(120);

       const QString willtopic = pub_topic_status+client_id;
       QString willmsg ="false";

       m_client->setWillTopic(willtopic);
       m_client->setWillMessage(willmsg.toStdString().c_str());

       connect_broker_timer = new QTimer;
       connect_broker_timer->setSingleShot(true);

       pub_topic_status_timer = new QTimer;
       pub_topic_status_timer->setSingleShot(true);
       pub_topic_status_timer->setInterval(100);

       pub_topic_resp_timer = new QTimer;
       pub_topic_resp_timer->setSingleShot(true);
       pub_topic_resp_timer->setInterval(300);

       sub_topic_cmd_timer = new QTimer;
       sub_topic_cmd_timer->setSingleShot(true);
       sub_topic_cmd_timer->setInterval(300);

       sub_topic_trigger_timer = new QTimer;
       sub_topic_trigger_timer->setSingleShot(true);
       sub_topic_trigger_timer->setInterval(300);

       connect(connect_broker_timer, SIGNAL(timeout()), this, SLOT(ConnectBroker()));
       connect(pub_topic_status_timer, SIGNAL(timeout()), this, SLOT(pub_status_topic()));
       connect(sub_topic_cmd_timer, SIGNAL(timeout()), this, SLOT(sub_host_cmd_topic()));
       connect(pub_topic_resp_timer, SIGNAL(timeout()), this, SLOT(pub_response_topic()));
       connect(sub_topic_trigger_timer, SIGNAL(timeout()), this, SLOT(sub_trigger_topic()));

       connect(m_client, &QMqttClient::stateChanged, this, &mqtt::updateLogStateChange);
       connect(m_client, &QMqttClient::disconnected, this, &mqtt::brokerDisconnected);
       connect(m_client, &QMqttClient::connected, this, &mqtt::brokerConnected);

       connect(m_client, &QMqttClient::messageReceived, this, [this](const QByteArray &message, const QMqttTopicName &topic) {

           const QString content = QDateTime::currentDateTime().toString()
                       + QLatin1String(" Received Topic: ")
                       + topic.name()
                       + QLatin1String(" Message: ")
                       + message
                       + QLatin1Char('\n');

           Log()<<client_id<<":"<<content;

           m_cmd_mqtt =json_to_cmd->cmd_parsing(message);

           if(m_cmd_mqtt->m_cmd_cam == sys_cmd_resp::CMD_CAMERA_CONNECTED_CHECK)
           {
               pub_status_topic();
           }
           else if(m_cmd_mqtt->m_cmd_cam == sys_cmd_resp::CMD_CAMERA_SERVER_INFO)
           {
                m_resp_from_camserver->Client_ID = m_device_info.get_ClientID();
                m_resp_from_camserver->m_device_type = sys_cmd_resp::DEVICE_TYPE_USB_CAMERA;
                m_resp_from_camserver->ServerIP = getLocalInfo();
                m_resp_from_camserver->ServerPort = m_device_info.get_ServerPort();

                if(m_resp_from_camserver->ServerIP =="")
                {
                    m_resp_from_camserver->m_resp_cam = sys_cmd_resp::RESP_CAMERA_SERVER_INFO_FAIL;
                }
                 else
                {
                    m_resp_from_camserver->m_resp_cam = sys_cmd_resp::RESP_CAMERA_SERVER_INFO_SUCCESS;
                }

                Publish(pub_topic_resp + client_id, json_to_cmd->encode_resp(client_id, m_resp_from_camserver), 1, false);
           }
           else
           {
               emit sig_cmd_from_mqtt_to_camera(m_cmd_mqtt);
           }
       });

       connect(m_client, &QMqttClient::pingResponseReceived, this, [this]()
       {
            const QString content = QDateTime::currentDateTime().toString()
                        + QLatin1String(" PingResponse")
                        + QLatin1Char('\n');
           Log()<<client_id<<":"<<content;
        });

       updateLogStateChange();

       connect_broker_timer->start(1000);
}

mqtt::~mqtt()
{

}

/*
QString mqtt::get_device_name()
{
    QString filename = "/boot/config.txt";

    QFile file(filename);

    if(!file.open(QFile::ReadOnly))
    {
       Log() << " Could not open the file for reading";
    }

    QTextStream in(&file);

    const QString config = in.readAll();

    QString device_name = config.section("#",-1,-1);

    file.close();

    return device_name.simplified();
}

QString mqtt::get_broker_ip()
{

    QString filename = "/boot/config.txt";

    QFile file(filename);

    if(!file.open(QFile::ReadOnly))
    {
       Log() << " Could not open the file for reading";
    }

    QTextStream in(&file);

    const QString config = in.readAll();

    QString broker_ip = config.section("#",-2,-2);

    file.close();

    return broker_ip.simplified();
}
*/

void mqtt::setClientPort(int p)
{
    m_client->setPort(p);
}

void mqtt::ConnectBroker()
{
    if (m_client->state() == QMqttClient::Disconnected)
    {
        m_client->connectToHost();
    }
    else
    {
        m_client->disconnectFromHost();
    }
}

void mqtt::DisConnectBroker()
{
    exit(0);
}

void mqtt::updateLogStateChange()
{
    const QString content = QDateTime::currentDateTime().toString()
                    + QLatin1String(": State Change")
                    + QString::number(m_client->state())
                    + QLatin1Char('\n');
    Log()<<content;
}

void mqtt::brokerDisconnected()
{
    Log()<<client_id<<": DisConnected";

    /*Retry Broker connect*/
    connect_broker_timer->start(10);
}

void mqtt::brokerConnected()
{
    Log()<<"Connected";
    Log()<<"client_id :"<<client_id;

    pub_topic_status_timer->start(1000);
    sub_topic_cmd_timer->start(2000);
}

bool mqtt::Publish(QString topic, QString msg, quint8 Qos, bool retain)
{
    if (m_client->publish(QMqttTopicName(topic), msg.toUtf8(), Qos, retain) == -1)
    {
        Log()<<"Could not publish message";

        return false;
    }

    return true;
}

bool mqtt::Subscribe(QString topic)
{
    auto subscription = m_client->subscribe(topic);

    if (!subscription)
    {
           Log()<<"Could not subscribe. Is there a valid connection?";

           return false;
     }

    return true;
}

bool mqtt::pub_status_topic()
{
    if(Publish(pub_topic_status + client_id, "true", 1, false))
    {
        Log()<<client_id<<" :pub_status_topic success";

        sub_topic_cmd_timer->start();

        return true;
    }

    Log()<<client_id <<" :pub_status_topic failed";

    return false;
}

bool mqtt::pub_response_topic()
{
    if(Publish(pub_topic_resp + client_id, "true", 1, false))
    {
        Log()<<client_id<<" :pub_response_topic success";

//      sub_topic_trigger_timer->start();

        return true;
    }

    Log()<<client_id<<" :pub_response_topic failed";

    return false;
}

bool mqtt::sub_host_cmd_topic()
{
    if(Subscribe(sub_topic_cmd + client_id))
    {
        Log()<<client_id<<" :sub_host_cmd_topic success";

        pub_topic_resp_timer->start();

        return true;
    }

    Log()<<client_id<<" :sub_host_cmd_topic failed";

    return false;
}

bool mqtt::sub_trigger_topic()
{
    if(Subscribe(sub_topic_trigger + "+"))
    {
        Log()<<"sub_topic_trigger success";
        return true;
    }

    Log()<<"sub_topic_trigger failed";

    return false;
}

QString mqtt::getLocalInfo()
{
    QString localip;

    QNetworkInterface eth1Ip = QNetworkInterface::interfaceFromName("eth0");
    QList<QNetworkAddressEntry> entries = eth1Ip.addressEntries();

    if (!entries.isEmpty())
    {
        QNetworkAddressEntry entry = entries.first();
        Log() << entry.ip();

        localip = entry.ip().toString();
    }

    return localip;
}

void mqtt::resp_operation(sys_cmd_resp *resp)
{

#if 1
    Log();
    Publish(pub_topic_resp + client_id, json_to_cmd->encode_resp(client_id, resp), 1, false);

#else
    switch(resp->m_resp_cam)
    {
        case sys_cmd_resp::RESP_CAMERA_CONNECTED_CHECK_SUCCESS:
        break;

        case sys_cmd_resp::RESP_CAMERA_SERVER_INFO_SUCCESS:
        break;

        case sys_cmd_resp::RESP_CAMERA_SET_ROI_PARAMETER_SUCCESS:
        break;

        case sys_cmd_resp::RESP_CAMERA_SET_TRIGGER_INTERVAL_SUCCESS:
        break;

        case sys_cmd_resp::RESP_CAMERA_OPEN_SUCCESS:

        break;

        case sys_cmd_resp::RESP_CAMERA_CAPTURE_SUCCESS:
        break;

        case sys_cmd_resp::RESP_CAMERA_CLOSE_SUCCESS:
        break;

        case sys_cmd_resp::RESP_CAMERA_IMG_SEND_ONE_FRAME_SUCCESS:
        break;

        case sys_cmd_resp::RESP_CAMERA_SEND_ROI_IMG_SUCCESS:
        break;

        case sys_cmd_resp::RESP_CAMERA_CONNECTED_CHECK_FAIL:
        break;

        case sys_cmd_resp::RESP_CAMERA_SERVER_INFO_FAIL:
        break;

        case sys_cmd_resp::RESP_CAMERA_SET_ROI_PARAMETER_FAIL:
        break;

        case sys_cmd_resp::RESP_CAMERA_SET_TRIGGER_INTERVAL_FAIL:
        break;

        case sys_cmd_resp::RESP_CAMERA_OPEN_FAIL:
        break;

        case sys_cmd_resp::RESP_CAMERA_CAPTURE_FAIL:
        break;

        case sys_cmd_resp::RESP_CAMERA_CLOSE_FAIL:
        break;

        case sys_cmd_resp::RESP_CAMERA_IMG_SEND_ONE_FRAME_FAIL:
        break;

        case sys_cmd_resp::RESP_CAMERA_SEND_ROI_IMG_FAIL:
        break;

        case sys_cmd_resp::RESP_CAMERA_UNKNOWN:
        break;
    }
#endif
}
