#include "controller.h"

controller::controller(QObject *parent) : QObject(parent)
{
    m_command = new cli_monitor;
    cmd_host = new sys_cmd_resp;

    camera_init_timer = new QTimer(this);
    camera_init_timer->setSingleShot(true);

    camera_capture_timer = new QTimer(this);
    camera_capture_timer->setSingleShot(true);

    /*Create TCP Socket Server*/
    m_socket_server = new SocketServer;

    /*create Camera Thread*/
    m_camera = new CameraThread;
    m_pCameraThread= new QThread(this);

    m_camera->moveToThread(m_pCameraThread);
    connect(m_pCameraThread, &QThread::finished, m_camera, &QObject::deleteLater);

    /*Create MQTT*/
    m_mqttClient = new mqtt;

    /*OLED Display*/
    m_oled_display = new oled_display;
    m_poledThread = new QThread(this);

    m_oled_display->moveToThread(m_poledThread);
    connect(m_poledThread, &QThread::finished, m_oled_display, &QObject::deleteLater);

    /*connect command/response signal*/
    connect(this, SIGNAL(sig_cmd_camera_from_main(sys_cmd_resp*)), m_camera, SLOT(operation(sys_cmd_resp*)));
    connect(m_mqttClient, SIGNAL(sig_cmd_from_mqtt_to_camera(sys_cmd_resp*)), m_camera, SLOT(operation(sys_cmd_resp*)));

    /*connecto Camera to TCP socket server*/
    connect(m_camera, SIGNAL(sig_send_image_file(void*,QString,quint32,quint8)), m_socket_server, SLOT(sendAttachment_click(void*,QString,quint32,quint8)));

    m_pCameraThread->start();
    m_poledThread->start();

    camera_init_timer->start(3000);

    connect(camera_capture_timer, &QTimer::timeout, [=]()
    {
        cmd_host->m_cmd_cam = sys_cmd_resp::CMD_CAMERA_CAPTURE;
        emit sig_cmd_camera_from_main(cmd_host);

        capture_count++;

        if(capture_count<100)
        {
            cmd_host->triggeer_interval +=100;
            camera_capture_timer->start(50);
        }
        else
        {
            cmd_host->triggeer_interval = 0;
            capture_count=0;
        }
    });

    connect(camera_init_timer, &QTimer::timeout, [=]()
    {
        cmd_host->m_cmd_cam = sys_cmd_resp::CMD_CAMERA_OPEN;
        emit sig_cmd_camera_from_main(cmd_host);
    });
}

controller::~controller()
{

}
