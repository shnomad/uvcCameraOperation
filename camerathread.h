#ifndef CAMERATHREAD_H
#define CAMERATHREAD_H

#include <QObject>
#include "libuvc/libuvc.h"
#include "jpeglib.h"
#include "sys_cmd_resp.h"

class CameraThread : public QObject
{
    Q_OBJECT
public:
    explicit CameraThread(QObject *parent = nullptr);
    ~CameraThread();
     static void cb(uvc_frame_t *frame, void *ptr);

     sys_cmd_resp *resp_cam;

signals:
     void sig_image_save_start();
     void sig_send_image_file(void *img, QString img_name, quint32 img_size, quint8);

public slots:
    void operation(sys_cmd_resp *);

private:
    void init();
    void open();
    void capture_ready();
//    void capture();
    //void capture(QString);
    void capture(QString, sys_cmd_resp::camera_capture_mode);
    void close();

    /*parameter for UVC Camera*/
    uvc_context_t *ctx;
    uvc_device_t *dev;
    uvc_device_handle_t *devh;
    uvc_stream_ctrl_t ctrl;
    uvc_error_t res;
    uvc_stream_handle_t *m_strmh;
    uvc_frame_t* captured_frame;

    /*JPEG Image Buffer*/
    QVector<QByteArray> imageBuffer;
    QVector<QString> imageNameBuffer;
};

#endif // CAMERATHREAD_H
