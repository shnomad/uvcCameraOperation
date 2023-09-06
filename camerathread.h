#ifndef CAMERATHREAD_H
#define CAMERATHREAD_H

#include <QObject>
#include "jpeglib.h"
#include <gphoto2/gphoto2.h>
#include <gphoto2/gphoto2-camera.h>
#include "sys_cmd_resp.h"

class CameraThread : public QObject
{
    Q_OBJECT
public:
    explicit CameraThread(QObject *parent = nullptr);
    ~CameraThread();
//   static void cb(uvc_frame_t *frame, void *ptr);
     sys_cmd_resp *resp_cam;

signals:
     void sig_image_save_start();
     void sig_send_image_file(void *img, QString img_name, quint32 img_size, quint8);
     void sig_resp_cam_cmd(sys_cmd_resp *);

public slots:
    void operation(sys_cmd_resp *);

private:
    void init();
    void OPen();
    void capture_ready();
    void capture(QString, sys_cmd_resp::camera_capture_mode);
    void close();

    /*Theta Camera functions*/
    void capture_to_memory(Camera *camera, GPContext *context, const char **ptr, unsigned long int *size);
    void capture_to_file(Camera *camera, GPContext *context, char *fn);

    Camera *camera;
    GPContext	*context;
    CameraText	text;

    /*JPEG Image Buffer*/
    QVector<QByteArray> imageBuffer;
    QVector<QString> imageNameBuffer;

    bool isCameraCaptureEnable = false;
};

#endif // CAMERATHREAD_H
