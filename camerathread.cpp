#include <QFile>
#include "camerathread.h"
#include "common.h"

CameraThread::CameraThread(QObject *parent) : QObject(parent)
{
    resp_cam = new sys_cmd_resp;

    connect(this, &CameraThread::sig_image_save_start, [&]()
    {
        Log()<<"file save start";

        do{

           QFile file(imageNameBuffer.front());

          if (file.open(QIODevice::WriteOnly))
          {
              file.write(imageBuffer.front());
              file.close();

              imageBuffer.erase(imageBuffer.begin());
              imageNameBuffer.erase(imageNameBuffer.begin());
          }

        }while(!imageBuffer.empty() && !imageNameBuffer.empty());

        Log()<<"file save end";
    });
}

CameraThread::~CameraThread()
{

}

void CameraThread::cb(uvc_frame_t *frame, void *ptr)
{
    Q_UNUSED(frame);
    Q_UNUSED(ptr);
}

void CameraThread::init()
{

    /* Initialize a UVC service context. Libuvc will set up its own libusb
     * context. Replace NULL with a libusb_context pointer to run libuvc
     * from an existing libusb context. */
    res = uvc_init(&ctx, nullptr);

    if (res < 0)
    {
          uvc_perror(res, "uvc_init");
          exit(0);
    }

    Log()<<"UVC initialized";

    /* Locates the first attached UVC device, stores in dev */
    res = uvc_find_device(ctx, &dev,0, 0, nullptr); /* filter devices: vendor_id, product_id, "serial_num" */

    if (res < 0)
    {
        uvc_perror(res, "uvc_find_device"); /* no devices found */
        exit(0);
    }
    else
    {
      Log()<<"Device found";
    }
}

void CameraThread::open()
{
    init();

    /* Try to open the device: requires exclusive access */
    res = uvc_open(dev, &devh);

    if (res < 0)
    {
          uvc_perror(res, "uvc_open"); /* unable to open device */
//        exit(0);
    }
    else
    {
      Log()<<"Device opened";

      /* Print out a message containing all the information that libuvc
       * knows about the device */
         uvc_print_diag(devh, stderr);

      /* Try to negotiate a 2592x1944 30 fps MJPG stream profile */
      res = uvc_get_stream_ctrl_format_size(
          devh, &ctrl, /* result stored in ctrl */
          UVC_COLOR_FORMAT_MJPEG, /* YUV 422, aka YUV 4:2:2. try _COMPRESSED */
          2592, 1944, 30 /* width, height, fps */
      );

      /* Print out the result */
      uvc_print_stream_ctrl(&ctrl, stderr);

      if (res < 0)
      {
        uvc_perror(res, "get_mode"); /* device doesn't provide a matching stream */
        exit(0);
      }
      else
      {
          capture_ready();
      }
   }

}

void CameraThread::capture_ready()
{
    captured_frame = uvc_allocate_frame(ctrl.dwMaxVideoFrameSize);

    res = uvc_stream_open_ctrl(devh, &m_strmh, &ctrl);

    res = uvc_stream_start(m_strmh, nullptr,nullptr,0);
}

void CameraThread::capture(QString trigger_value, sys_cmd_resp::camera_capture_mode capture_mode)
{
    res = uvc_stream_get_frame(m_strmh, &captured_frame,0);        

//  QDateTime Current_Time = QDateTime::currentDateTime();

   //QString filename = "/home/rt/capture_file/" +Current_Time.toString("yyyyMMddhhmmsszzz") + ".jpg";
     QString filename = trigger_value + ".jpg";
   //QString filename = "/home/rt/capture_file/" +trigger_value + ".jpg";

//   Log()<<filename;

     emit sig_send_image_file(captured_frame->data, filename, captured_frame->data_bytes, static_cast<quint8>(capture_mode));     

//   imageBuffer.push_back(QByteArray(static_cast<const char*>(captured_frame->data), captured_frame->data_bytes));
//   imageNameBuffer.push_back(filename);
/*
   if(imageBuffer.length()==100 && imageNameBuffer.length()==100)
   {
        emit sig_image_save_start();
   }
*/
/*
    FILE *fp;

    fp = fopen(filename.toStdString().c_str(), "w");

    fwrite(captured_frame->data, 1, captured_frame->data_bytes, fp);

    fclose(fp);

    Log();
*/
}

void CameraThread::close()
{
    uvc_close(devh);
    Log()<<"Device closed";

    /* Release the device descriptor */
    uvc_unref_device(dev);

    /* Close the UVC context. This closes and cleans up any existing device handles,
    * and it closes the libusb context if one was not provided. */
    uvc_exit(ctx);
    Log()<<"UVC exited";
}

void CameraThread::operation(sys_cmd_resp *cmd)
{
     Log()<<QVariant::fromValue(cmd->m_cmd_cam).toString();

     switch(cmd->m_cmd_cam)
     {
        case sys_cmd_resp::CMD_CAMERA_SET_ROI_PARAMETER:

        break;

        case sys_cmd_resp::CMD_CAMERA_SET_TRIGGER_INTERVAL:
         break;

        case sys_cmd_resp::CMD_CAMERA_OPEN:

         open();

        break;

        case sys_cmd_resp::CMD_CAMERA_CAPTURE:         

         Log()<<"cmd->triggeer_interval :"<<cmd->triggeer_interval;

         capture(QString("%1").arg(cmd->triggeer_interval, 7, 'g', -1, '0'), cmd->m_camera_capture_mode);

        break;

        case sys_cmd_resp::CMD_CAMERA_CLOSE:

         close();

        break;

        case sys_cmd_resp::CMD_CAMERA_IMG_SEND_ONE_FRAME:
        break;

        case sys_cmd_resp::CMD_CAMERA_IMG_SEND_CONCAT:

        break;

        case sys_cmd_resp::CMD_CAMERA_SERVER_INFO:

        break;

        case sys_cmd_resp::CMD_CAMERA_UNKNOWN:
        break;
     }
}
