#include "controller.h"

controller::controller(QObject *parent) : QObject(parent)
{
    m_command = new cli_monitor;
    cmd_host = new sys_cmd_resp;
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

    /*connect command/response signal*/
    connect(this, SIGNAL(sig_cmd_camera_from_main(sys_cmd_resp*)), m_camera, SLOT(operation(sys_cmd_resp*)));
    connect(m_mqttClient, SIGNAL(sig_cmd_from_mqtt_to_camera(sys_cmd_resp*)), m_camera, SLOT(operation(sys_cmd_resp*)));

    /*connecto Camera to TCP socket server*/
    connect(m_camera, SIGNAL(sig_send_image_file(void*, QString,quint32)), m_socket_server, SLOT(sendAttachment_click(void*, QString, quint32)));

    m_pCameraThread->start();

    connect(camera_capture_timer, &QTimer::timeout, [=]()
    {
        cmd_host->m_cmd_cam = sys_cmd_resp::CMD_CAMERA_CAPTURE;
        emit sig_cmd_camera_from_main(cmd_host);

        capture_count++;

        if(capture_count<100)
            camera_capture_timer->start(50);
        else
            capture_count=0;
    });
}

controller::~controller()
{

}
