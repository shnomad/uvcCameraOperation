#include <QFile>
#include "camerathread.h"
#include "common.h"
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <QTextStream>
#include "samples.h"

static void ctx_error_func (GPContext *context, const char *str, void *data)
{
        fprintf  (stderr, "\n*** Contexterror ***              \n%s\n",str);
        fflush   (stderr);
}

static void ctx_status_func (GPContext *context, const char *str, void *data)
{
        fprintf  (stderr, "%s\n", str);
        fflush   (stderr);
}

GPContext* sample_create_context()
{
    GPContext *context;

    /* This is the mandatory part */
        context = gp_context_new();

    /* All the parts below are optional! */
        gp_context_set_error_func (context, ctx_error_func, NULL);
        gp_context_set_status_func (context, ctx_status_func, NULL);

    /* also:
        gp_context_set_cancel_func    (p->context, ctx_cancel_func,  p);
        gp_context_set_message_func   (p->context, ctx_message_func, p);
        if (isatty (STDOUT_FILENO))
        gp_context_set_progress_funcs (p->context,
        ctx_progress_start_func, ctx_progress_update_func,
        ctx_progress_stop_func, p);
     */
    return context;
}

CameraThread::CameraThread(QObject *parent) : QObject(parent)
{
    resp_cam = new sys_cmd_resp;

    init();

    isCameraCaptureEnable = true;

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

void CameraThread::init()
{
    /*gphoto2 handler*/
    int     ret;    
//  unsigned long size;

    context = sample_create_context (); /* see context.c */
    gp_camera_new (&camera);

    /* This call will autodetect cameras, take the
     * first one from the list and use it. It will ignore
     * any others... See the *multi* examples on how to
     * detect and use more than the first one.
     */
    ret = gp_camera_init (camera, context);

    if (ret < GP_OK)
    {
        Log()<<"No camera auto detected";
        gp_camera_free (camera);
    }
#if 0
    /* Simple query the camera summary text */
    ret = gp_camera_get_summary (camera, &text, context);

    if (ret < GP_OK)
    {
        Log()<<"Camera failed retrieving summary.\n";
        gp_camera_free (camera);
    }

    /*
     *
        "Manufacturer: Ricoh Company, Ltd."
        "Model: RICOH THETA Z1"
        "Version: 2.30.1"
        "Serial Number: 32100
    */

     QString thetainfo(text.text);

     QStringList Lines = thetainfo.split('\n');

     for (int i = 0; i <4; i++)
      {
            Log()<<Lines[i];
            resp_cam->theta_info << Lines[i];
      }

     resp_cam->m_resp_cam = sys_cmd_resp::RESP_CAMERA_OPEN_SUCCESS;
     emit sig_resp_cam_cmd(resp_cam);

    /* Simple query of a string configuration variable. */
    ret = get_config_value_string (camera, "owner", &owner, context);

    if (ret >= GP_OK)
    {
        printf("Owner: %s\n", owner);
        free (owner);
    }
#endif

//    capture_to_file(camera, context, "/home/rt/theta_img");
//    capture_to_memory(camera, context, (const char**)&data, &size);
//    capture("20230831.jpg", sys_cmd_resp::CAPTURE_MODE_TEST);
}


void CameraThread::OPen()
{
    int     ret;
    char    *owner;

    /* Simple query the camera summary text */
    ret = gp_camera_get_summary (camera, &text, context);

    if (ret < GP_OK)
    {
        Log()<<"Camera failed retrieving summary.\n";
        gp_camera_free (camera);
    }

    /*
     *
        "Manufacturer: Ricoh Company, Ltd."
        "Model: RICOH THETA Z1"
        "Version: 2.30.1"
        "Serial Number: 32100
    */

     QString thetainfo(text.text);

     QStringList Lines = thetainfo.split('\n');

     for (int i = 0; i <4; i++)
      {
            Log()<<Lines[i];
            resp_cam->theta_info << Lines[i];
      }    

     resp_cam->m_resp_cam = sys_cmd_resp::RESP_CAMERA_OPEN_SUCCESS;
     emit sig_resp_cam_cmd(resp_cam);

    /* Simple query of a string configuration variable. */
    ret = get_config_value_string (camera, "owner", &owner, context);

    if (ret >= GP_OK)
    {
        printf("Owner: %s\n", owner);
        free (owner);
    }
}

void CameraThread::capture_ready()
{

}

void CameraThread::capture(QString trigger_value, sys_cmd_resp::camera_capture_mode capture_mode)
{    
    char    *owner, *data;
    unsigned long size;

    QString filename = trigger_value + ".jpg";

    capture_to_memory(camera, context, (const char**)&data, &size);

    emit sig_send_image_file(data, filename, size, static_cast<quint8>(capture_mode));

/*
    QByteArray tmp_buf = QByteArray::fromRawData(data, size);

    QFile f("/home/rt/test.jpg");

    if(f.open(QIODevice::WriteOnly))
    {
        f.write(tmp_buf);
    }

    f.close();
*/

}

void CameraThread::capture_to_memory(Camera *camera, GPContext *context, const char **ptr, unsigned long int *size)
{
    int retval;
    CameraFile *file;
    CameraFilePath camera_file_path;

    Log()<<"Capturing";

    /* NOP: This gets overridden in the library to /capt0000.jpg */
    strcpy(camera_file_path.folder, "/store_00020001/DCIM/100RICOH/");
    strcpy(camera_file_path.name, "foo.jpg");

    retval = gp_camera_capture(camera, GP_CAPTURE_IMAGE, &camera_file_path, context);
    Log()<<"Retval :"<< retval;

    Log()<< QString("Pathname on the camera: %1 %2").arg(camera_file_path.folder).arg(camera_file_path.name);

    retval = gp_file_new(&file);
    Log()<<"Retval: "<<retval;
    retval = gp_camera_file_get(camera, camera_file_path.folder, camera_file_path.name, GP_FILE_TYPE_NORMAL, file, context);
    Log()<<"Retval: "<<retval;

    gp_file_get_data_and_size (file, ptr, size);
#if 0
    tmp_buf = QByteArray::fromRawData(*ptr, *size);

    QFile f("/home/rt/test.jpg");

    if(f.open(QIODevice::WriteOnly))
    {
        f.write(tmp_buf);
    }

    f.close();
#endif

    Log()<<"Deleting";
    retval = gp_camera_file_delete(camera, camera_file_path.folder, camera_file_path.name, context);
    Log()<<"Retval: %d\n";
}

void CameraThread::capture_to_file(Camera *camera, GPContext *context, char *fn)
{
    int		fd, retval;
    CameraFile	*file;
    CameraFilePath	camera_file_path;
    CameraFileInfo	info;

    Log()<<"Capturing.\n";

    /* NOP: This gets overridden in the library to /capt0000.jpg */
    strcpy(camera_file_path.folder, "/store_00020001/DCIM/100RICOH/");
    strcpy(camera_file_path.name, "foo.jpg");

    Log()<<"capture Start";
    retval = gp_camera_capture(camera, GP_CAPTURE_IMAGE, &camera_file_path, context);
    Log()<<"capture End";

    Log()<<"Retval:"<<retval;

// Log()<<"Pathname on the camera: %s/%s\n"<<camera_file_path.folder<<camera_file_path.name;

    Log()<< QString("Pathname on the camera: %1 %2").arg(camera_file_path.folder).arg(camera_file_path.name);

    retval = gp_camera_file_get_info (camera, camera_file_path.folder, camera_file_path.name, &info, context);

    Log()<<"file info reported flags: "<<info.file.fields;

    if (info.file.fields & GP_FILE_INFO_MTIME)
        Log()<<"info reported mtime: %ld\n"<<info.file.mtime;

    if (info.file.fields & GP_FILE_INFO_SIZE)
        Log()<<"info reported size: %ld\n"<<info.file.size;

    if (info.file.fields & GP_FILE_INFO_TYPE)
        Log()<<"info reported type: %s\n"<<info.file.type;

    fd = open(fn, O_CREAT | O_WRONLY | O_BINARY, 0644);

    retval = gp_file_new_from_fd(&file, fd);

    Log()<<"Retval: "<<retval;

    retval = gp_camera_file_get(camera, camera_file_path.folder, camera_file_path.name, GP_FILE_TYPE_NORMAL, file, context);

    Log()<<"Retval: "<<retval;

    gp_file_free(file);

    Log()<<"Deleting.\n";

    retval = gp_camera_file_delete(camera, camera_file_path.folder, camera_file_path.name, context);

    Log()<<"Retval: "<<retval;
}

void CameraThread::close()
{
    gp_camera_exit (camera, context);
    gp_camera_free (camera);
    gp_context_unref (context);
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
            OPen();
        break;

        case sys_cmd_resp::CMD_CAMERA_CAPTURE:         

           Log()<<"isCameraCaptureEnable :"<<isCameraCaptureEnable;

          //cmd->m_camera_capture_mode = sys_cmd_resp::CAPTURE_MODE_TEST;

           if(isCameraCaptureEnable ==true || cmd->m_camera_capture_mode == sys_cmd_resp::CAPTURE_MODE_TEST)
           {
                 Log()<<"cmd->triggeer_interval :"<<cmd->m_trigger_distance_total;

                 isCameraCaptureEnable = false;

                 capture(QString("%1").arg(cmd->m_trigger_distance_total, 7, 'g', -1, '0'), cmd->m_camera_capture_mode);

                 isCameraCaptureEnable = true;
           }           

           Log()<<"isCameraCaptureEnable :"<<isCameraCaptureEnable;

        break;

        case sys_cmd_resp::CMD_CAMERA_CAPTURE_ENABLE:

         /*When Survey Ready, sent from Road Image Logger*/
            isCameraCaptureEnable = true;
            Log()<<isCameraCaptureEnable;

        break;

        case sys_cmd_resp::CMD_CAMERA_CAPTURE_DISABLE:

         /*When Survey Ready, sent from Road Image Logger*/
            isCameraCaptureEnable = false;
            Log()<<isCameraCaptureEnable;

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
