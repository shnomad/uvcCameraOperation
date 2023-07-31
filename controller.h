#ifndef CONTROLLER_H
#define CONTROLLER_H

#include <QObject>
#include <QThread>
#include <QTimer>
#include "socketserver.h"
#include "camerathread.h"
#include "cli_monitor.h"
#include "oled_display.h"
#include "mqtt.h"
//#include "image_post_process.h"

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

    /*TCP Socket server*/
    SocketServer *m_socket_server;

    /*MQTT*/
     mqtt *m_mqttClient;

    /*Camera Thread*/
    QThread *m_pCameraThread;
    CameraThread *m_camera;

    /*Image process thread*/
//    QThread *m_pImagePostProcessThread;
//    image_post_process *m_img_PostProcess;

    /*oled display*/                
    oled_display *m_oled_display;
    QThread *m_poledThread;

    cli_monitor *m_command;
    sys_cmd_resp *cmd_host;
    QTimer *camera_capture_timer;
    quint32 capture_count=0;

    QTimer *camera_init_timer;
    bool dispay_status_msg = false;

};

#endif // CONTROLLER_H
