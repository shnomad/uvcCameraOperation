#ifndef SYS_CMD_RESP_H
#define SYS_CMD_RESP_H

#include <QObject>

class sys_cmd_resp : public QObject
{
    Q_OBJECT
public:
    explicit sys_cmd_resp(QObject *parent = nullptr);

    enum cmd_cam{CMD_CAMERA_CONNECTED_CHECK=0x10, CMD_CAMERA_SERVER_INFO, CMD_CAMERA_SET_ROI_PARAMETER, CMD_CAMERA_SET_TRIGGER_INTERVAL,\
                 CMD_CAMERA_OPEN, CMD_CAMERA_CAPTURE, CMD_CAMERA_CAPTURE_ENABLE, CMD_CAMERA_CAPTURE_DISABLE, CMD_CAMERA_CLOSE, CMD_CAMERA_IMG_SEND_ONE_FRAME, CMD_CAMERA_IMG_SEND_CONCAT,\
                 CMD_CAMERA_UNKNOWN=0x1f};Q_ENUM(cmd_cam)
    enum resp_cam{RESP_CAMERA_CONNECTED_CHECK_SUCCESS=0x20, RESP_CAMERA_SERVER_INFO_SUCCESS, RESP_CAMERA_SET_ROI_PARAMETER_SUCCESS,\
                RESP_CAMERA_SET_TRIGGER_INTERVAL_SUCCESS, RESP_CAMERA_OPEN_SUCCESS, RESP_CAMERA_CAPTURE_SUCCESS, \
                RESP_CAMERA_CLOSE_SUCCESS, RESP_CAMERA_IMG_SEND_ONE_FRAME_SUCCESS, RESP_CAMERA_SEND_ROI_IMG_SUCCESS, \
                RESP_CAMERA_CONNECTED_CHECK_FAIL=0x30, RESP_CAMERA_SERVER_INFO_FAIL,\
                RESP_CAMERA_SET_ROI_PARAMETER_FAIL, RESP_CAMERA_SET_TRIGGER_INTERVAL_FAIL, RESP_CAMERA_OPEN_FAIL, RESP_CAMERA_CAPTURE_FAIL, \
                RESP_CAMERA_CLOSE_FAIL, RESP_CAMERA_IMG_SEND_ONE_FRAME_FAIL, RESP_CAMERA_SEND_ROI_IMG_FAIL, RESP_CAMERA_UNKNOWN};Q_ENUM(resp_cam)

    enum device_type{
            DEVICE_TYPE_USB_CAMERA=0x0,
            DEVICE_TYPE_DISTANCE_MEASUREMENT_INSTRUMENT,
            DEVICE_TYPE_UNKNOWN
        };

    enum camera_capture_mode{
        CAPTURE_MODE_NORMAL=0x0,
        CAPTURE_MODE_TEST,
        CAPTURE_MODE_UNKNOWN = 0xf,
    };Q_ENUM(camera_capture_mode)

     QStringList theta_info;
//    QString theta_info;

    QString Client_ID = "";
    QString ServerIP ="";
    QString ServerPort ="";
    quint32 m_set_trigger_distance =0;
    double m_trigger_distance_total=0.0;

    struct roi_geometry{
        quint32 x0;
        quint32 x1;
        quint32 x2;
        quint32 x3;
        quint32 y0;
        quint32 y1;
        quint32 y2;
        quint32 y3;
    };

    cmd_cam m_cmd_cam = CMD_CAMERA_UNKNOWN;
    resp_cam m_resp_cam = RESP_CAMERA_UNKNOWN;
    device_type m_device_type = DEVICE_TYPE_UNKNOWN;
    camera_capture_mode m_camera_capture_mode = CAPTURE_MODE_UNKNOWN;

signals:

public slots:
};

#endif // SYS_CMD_RESP_H
