#include "jsondatahandle.h"
#include "common.h"
#include <typeinfo>

JsonDataHandle::JsonDataHandle(QObject *parent) : QObject(parent)
{
    cmd_from_host = new sys_cmd_resp;
}

JsonDataHandle::~JsonDataHandle()
{

}

QString JsonDataHandle::encode_resp(QString channel,sys_cmd_resp *response)
{
   QJsonObject mainObject;

   quint8 resp_number = static_cast<quint8>(response->m_resp_cam);

   mainObject.insert("channel", channel);
   mainObject.insert("response", resp_number);

   switch(response->m_resp_cam)
   {
       case sys_cmd_resp::RESP_CAMERA_CONNECTED_CHECK_SUCCESS:
       break;

       case sys_cmd_resp::RESP_CAMERA_SERVER_INFO_SUCCESS:
            mainObject.insert("deviceType", static_cast<quint8>(response->m_device_type));
            mainObject.insert("serverIP", response->ServerIP);
            mainObject.insert("serverPort", response->ServerPort);
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

    QJsonDocument jsonDoc(mainObject);

    jsonDoc.setObject(mainObject);

    /* Write our jsondocument as json with JSON format */
     QString encode_data = QString::fromUtf8(jsonDoc.toJson());

     return encode_data;
}

//sys_cmd_resp::cmd_cam JsonDataHandle::cmd_parsing(QString message)
sys_cmd_resp* JsonDataHandle::cmd_parsing(QString message)
{    
    QJsonDocument jsonDoc =  QJsonDocument::fromJson(message.toUtf8());
    QJsonObject jsonObj = jsonDoc.object();
    QJsonValue cmd = jsonObj.value("command");

    quint8 temp_cmd = static_cast<quint8>(cmd.toInt());

    cmd_from_host->m_cmd_cam = static_cast<sys_cmd_resp::cmd_cam>(temp_cmd);

    //switch(static_cast<quint8>(cmd.toInt()))
    switch(cmd_from_host->m_cmd_cam)
    {
        case sys_cmd_resp::CMD_CAMERA_CONNECTED_CHECK:

        break;

        case sys_cmd_resp::CMD_CAMERA_SERVER_INFO:

            cmd_from_host->m_cmd_cam = sys_cmd_resp::CMD_CAMERA_SERVER_INFO;

        break;

        case sys_cmd_resp::CMD_CAMERA_SET_ROI_PARAMETER:

        break;

        case sys_cmd_resp::CMD_CAMERA_SET_TRIGGER_INTERVAL:
        case sys_cmd_resp::CMD_CAMERA_OPEN:
        case sys_cmd_resp::CMD_CAMERA_CAPTURE:
            {
              QJsonValue trigger = jsonObj.value("trigger");
              QString trigger_tmp = trigger.toString();

              cmd_from_host->triggeer_interval = trigger_tmp.toInt();

              Log()<<"cmd_from_host->triggeer_interval :"<<cmd_from_host->triggeer_interval;
            }

        break;
        case sys_cmd_resp::CMD_CAMERA_CLOSE:

        break;

        case sys_cmd_resp::CMD_CAMERA_IMG_SEND_ONE_FRAME:

        break;

        case sys_cmd_resp::CMD_CAMERA_IMG_SEND_CONCAT:

        break;

        case sys_cmd_resp::CMD_CAMERA_UNKNOWN:

        break;
    }

    return cmd_from_host;
}
