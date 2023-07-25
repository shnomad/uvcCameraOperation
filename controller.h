#ifndef CONTROLLER_H
#define CONTROLLER_H

#include <QObject>
#include <QThread>
#include <QTimer>
#include "socketserver.h"
#include "camerathread.h"
#include "cli_monitor.h"
#include "mqtt.h"

class controller : public QObject
{
    Q_OBJECT
public:
    explicit controller(QObject *parent = nullptr);
    ~controller();

signals:
    void sig_cmd_camera_from_main(sys_cmd_resp *);

public slots:

private:
    /*OLED display*/
    void display_init();

    /*TCP Socket server*/
    SocketServer *m_socket_server;

    /*MQTT Thread*/
     mqtt *m_mqttClient;
     QThread *m_pmqttClientThread;

    /*Camera Thread*/
    QThread *m_pCameraThread;
    CameraThread *m_camera;
    cli_monitor *m_command;

    sys_cmd_resp *cmd_host;
    QTimer *camera_capture_timer;
    quint32 capture_count=0;

    QTimer *camera_init_timer, *oled_display_timer;
    unsigned char symbol_count =0;
    bool dispay_status_msg = false;

};

#endif // CONTROLLER_H
