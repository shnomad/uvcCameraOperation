#include "settings.h"
#include <QCoreApplication>

static settings* m_pInstance = NULL;
settings *settings::Instance()
{
    if (!m_pInstance)
    {
        m_pInstance = new settings();
    }

    return m_pInstance;
}

settings::settings(QObject *parent) : QSettings(getAppPath() + "/settings.ini", QSettings::IniFormat, parent)
{
    if(value(rdth_survey_set).isNull() == true)
    {
        setValue(rdth_survey_set,true);

        setDMIinterval(100);

        setValue(rdth_camera_front_description,"");
        setValue(rdth_camera_left_description,"");
        setValue(rdth_camera_right_description,"");
        setValue(rdth_camera_rear_description,"");

        setValue(rdth_camera_front_trigger_interval,1000);
        setValue(rdth_camera_left_trigger_interval,1000);
        setValue(rdth_camera_right_trigger_interval,1000);
        setValue(rdth_camera_rear_trigger_interval,1000);

        setValue(rdth_camera_front_resolution,"");
        setValue(rdth_camera_left_resolution,"");
        setValue(rdth_camera_right_resolution,"");
        setValue(rdth_camera_rear_resolution,"");

        setValue(rdth_image_roi_camera_front_c_x0_position, "");
        setValue(rdth_image_roi_camera_front_c_x1_position, "");
        setValue(rdth_image_roi_camera_front_c_x2_position, "");
        setValue(rdth_image_roi_camera_front_c_x3_position, "");
        setValue(rdth_image_roi_camera_front_c_y0_position, "");
        setValue(rdth_image_roi_camera_front_c_y1_position, "");
        setValue(rdth_image_roi_camera_front_c_y2_position, "");
        setValue(rdth_image_roi_camera_front_c_y3_position, "");

        setValue(rdth_image_roi_camera_left_c_x0_position, "");
        setValue(rdth_image_roi_camera_left_c_x1_position, "");
        setValue(rdth_image_roi_camera_left_c_x2_position, "");
        setValue(rdth_image_roi_camera_left_c_x3_position, "");
        setValue(rdth_image_roi_camera_left_c_y0_position, "");
        setValue(rdth_image_roi_camera_left_c_y1_position, "");
        setValue(rdth_image_roi_camera_left_c_y2_position, "");
        setValue(rdth_image_roi_camera_left_c_y3_position, "");

        setValue(rdth_image_roi_camera_right_c_x0_position, "");
        setValue(rdth_image_roi_camera_right_c_x1_position, "");
        setValue(rdth_image_roi_camera_right_c_x2_position, "");
        setValue(rdth_image_roi_camera_right_c_x3_position, "");
        setValue(rdth_image_roi_camera_right_c_y0_position, "");
        setValue(rdth_image_roi_camera_right_c_y1_position, "");
        setValue(rdth_image_roi_camera_right_c_y2_position, "");
        setValue(rdth_image_roi_camera_right_c_y3_position, "");

        setValue(rdth_image_roi_camera_rear_c_x0_position, "");
        setValue(rdth_image_roi_camera_rear_c_x1_position, "");
        setValue(rdth_image_roi_camera_rear_c_x2_position, "");
        setValue(rdth_image_roi_camera_rear_c_x3_position, "");
        setValue(rdth_image_roi_camera_rear_c_y0_position, "");
        setValue(rdth_image_roi_camera_rear_c_y1_position, "");
        setValue(rdth_image_roi_camera_rear_c_y2_position, "");
        setValue(rdth_image_roi_camera_rear_c_y3_position, "");
    }
}

settings::~settings()
{

}

QString settings::getCameraFront_Description()
{
    return value(rdth_camera_front_description).toString();
}

QString settings::getCameraLeft_Description()
{
    return value(rdth_camera_left_description).toString();
}

QString settings::getCameraRight_Description()
{
    return value(rdth_camera_right_description).toString();
}

QString settings::getCameraRear_Description()
{
    return value(rdth_camera_rear_description).toString();
}

uint settings::getCameraFront_trigger_interval()
{
    return value(rdth_camera_front_trigger_interval).toUInt();
}

uint settings::getCameraLeft_trigger_interval()
{
    return value(rdth_camera_left_trigger_interval).toUInt();
}

uint settings::getCameraRight_trigger_interval()
{
    return value(rdth_camera_right_trigger_interval).toUInt();
}

uint settings::getCameraRear_trigger_interval()
{
    return value(rdth_camera_rear_trigger_interval).toUInt();
}

QString settings::getDMI_Information()
{
    return value(rdth_dmi_information).toString();
}


bool settings::getIsDMIused()
{
    return value(rdth_dmi_isUsed).toBool();
}

quint32 settings::getDMIinterval()
{
    return value(rdth_dmi_interval).toInt();
}

quint8 settings::getCameraFront_resolution()
{
    return value(rdth_camera_front_resolution).toUInt();
}

quint8 settings::getCameraLeft_resolution()
{
    return value(rdth_camera_left_resolution).toUInt();
}

quint8 settings::getCameraRight_resolution()
{
    return value(rdth_camera_right_resolution).toUInt();
}

quint8 settings::getCameraRear_resolution()
{
    return value(rdth_camera_rear_resolution).toUInt();
}

QString settings::getCameraFront_image_roi_c_x0()
{
    return value(rdth_image_roi_camera_front_c_x0_position).toString();
}

QString settings::getCameraFront_image_roi_c_y0()
{
    return value(rdth_image_roi_camera_front_c_y0_position).toString();
}

QString settings::getCameraFront_image_roi_c_x1()
{
    return value(rdth_image_roi_camera_front_c_x1_position).toString();
}

QString settings::getCameraFront_image_roi_c_y1()
{
    return value(rdth_image_roi_camera_front_c_y1_position).toString();
}

QString settings::getCameraFront_image_roi_c_x2()
{
    return value(rdth_image_roi_camera_front_c_x2_position).toString();
}

QString settings::getCameraFront_image_roi_c_y2()
{
    return value(rdth_image_roi_camera_front_c_y2_position).toString();
}

QString settings::getCameraFront_image_roi_c_x3()
{
    return value(rdth_image_roi_camera_front_c_x3_position).toString();
}

QString settings::getCameraFront_image_roi_c_y3()
{
    return value(rdth_image_roi_camera_front_c_y3_position).toString();
}

QString settings::getCameraLeft_image_roi_c_x0()
{
    return value(rdth_image_roi_camera_left_c_x0_position).toString();
}

QString settings::getCameraLeft_image_roi_c_y0()
{
    return value(rdth_image_roi_camera_left_c_y0_position).toString();
}

QString settings::getCameraLeft_image_roi_c_x1()
{
    return value(rdth_image_roi_camera_left_c_x1_position).toString();
}

QString settings::getCameraLeft_image_roi_c_y1()
{
    return value(rdth_image_roi_camera_left_c_y1_position).toString();
}

QString settings::getCameraLeft_image_roi_c_x2()
{
    return value(rdth_image_roi_camera_left_c_x2_position).toString();
}

QString settings::getCameraLeft_image_roi_c_y2()
{
    return value(rdth_image_roi_camera_left_c_y2_position).toString();
}

QString settings::getCameraLeft_image_roi_c_x3()
{
    return value(rdth_image_roi_camera_left_c_x3_position).toString();
}

QString settings::getCameraLeft_image_roi_c_y3()
{
    return value(rdth_image_roi_camera_left_c_y3_position).toString();
}

QString settings::getCameraRight_image_roi_c_x0()
{
    return value(rdth_image_roi_camera_right_c_x0_position).toString();
}

QString settings::getCameraRight_image_roi_c_y0()
{
    return value(rdth_image_roi_camera_right_c_y0_position).toString();
}

QString settings::getCameraRight_image_roi_c_x1()
{
    return value(rdth_image_roi_camera_right_c_x1_position).toString();
}

QString settings::getCameraRight_image_roi_c_y1()
{
    return value(rdth_image_roi_camera_right_c_y1_position).toString();
}

QString settings::getCameraRight_image_roi_c_x2()
{
    return value(rdth_image_roi_camera_right_c_x2_position).toString();
}

QString settings::getCameraRight_image_roi_c_y2()
{
    return value(rdth_image_roi_camera_right_c_y2_position).toString();
}

QString settings::getCameraRight_image_roi_c_x3()
{
    return value(rdth_image_roi_camera_right_c_x3_position).toString();
}

QString settings::getCameraRight_image_roi_c_y3()
{
    return value(rdth_image_roi_camera_right_c_y3_position).toString();
}

QString settings::getCameraRear_image_roi_c_x0()
{
    return value(rdth_image_roi_camera_rear_c_x0_position).toString();
}

QString settings::getCameraRear_image_roi_c_y0()
{
    return value(rdth_image_roi_camera_rear_c_y0_position).toString();
}

QString settings::getCameraRear_image_roi_c_x1()
{
    return value(rdth_image_roi_camera_rear_c_x1_position).toString();
}

QString settings::getCameraRear_image_roi_c_y1()
{
    return value(rdth_image_roi_camera_rear_c_y1_position).toString();
}

QString settings::getCameraRear_image_roi_c_x2()
{
    return value(rdth_image_roi_camera_rear_c_x2_position).toString();
}

QString settings::getCameraRear_image_roi_c_y2()
{
    return value(rdth_image_roi_camera_rear_c_y2_position).toString();
}

QString settings::getCameraRear_image_roi_c_x3()
{
    return value(rdth_image_roi_camera_rear_c_x3_position).toString();
}

QString settings::getCameraRear_image_roi_c_y3()
{
    return value(rdth_image_roi_camera_rear_c_y3_position).toString();
}

QString settings::getAppPath()
{
    return qApp->applicationDirPath();
}

const QHash<QString, QVariant> settings::getSettings()
{
    QHash<QString, QVariant> ret;
    QStringList keys = allKeys();

    foreach(QString key, keys)
    {
        //Log() << key << value(key);
        ret.insert(key, value(key));
    }
    return ret;
}

void settings::setSettings(const QHash<QString, QVariant> &settingValue)
{
    QStringList keys = settingValue.keys();
    setIniCodec("UTF-8");

    foreach(QString key, keys)
    {
        //Log() << key << settingValue.value(key);
        setValue(key, settingValue.value(key));
    }

    sync();
}

void settings::setSurveySet(bool set)
{
    setValue(rdth_survey_set, set);
    sync();
}

void settings::setCameraFront_Description(QString value)
{
    setValue(rdth_camera_front_description, value);
    sync();
}

void settings::setCameraLeft_Description(QString value)
{
    setValue(rdth_camera_left_description, value);
    sync();
}

void settings::setCameraRight_Description(QString value)
{
    setValue(rdth_camera_right_description, value);
    sync();
}

void settings::setCameraRear_Description(QString value)
{
    setValue(rdth_camera_rear_description, value);
    sync();
}

void settings::setCameraFront_trigger_interval(uint value)
{
    setValue(rdth_camera_front_trigger_interval, value);
    sync();
}

void settings::setCameraLeft_trigger_interval(uint value)
{
    setValue(rdth_camera_left_trigger_interval, value);
    sync();
}

void settings::setCameraRight_trigger_interval(uint value)
{
    setValue(rdth_camera_right_trigger_interval, value);
    sync();
}

void settings::setCameraRear_trigger_interval(uint value)
{
    setValue(rdth_camera_rear_trigger_interval, value);
    sync();
}

void settings::setDMI_Information(QString value)
{
    setValue(rdth_dmi_information, value);
    sync();
}

void settings::setIsDMI_use(bool value)
{
    setValue(rdth_dmi_isUsed, value);
    sync();
}

void settings::setDMIinterval(int value)
{
    setValue(rdth_dmi_interval, value);
    sync();
}

void settings::setCameraFront_resolution(QString value)
{
    setValue(rdth_camera_front_resolution, value);
    sync();
}

void settings::setCameraLeft_resolution(QString value)
{
    setValue(rdth_camera_left_resolution, value);
    sync();
}

void settings::setCameraRight_resolution(QString value)
{
    setValue(rdth_camera_right_resolution, value);
    sync();
}

void settings::setCameraRear_resolution(QString value)
{
    setValue(rdth_camera_rear_resolution, value);
    sync();
}

void settings::setCameraFront_image_roi_c_x0(QString value)
{
    setValue(rdth_image_roi_camera_front_c_x0_position, value);
    sync();
}

void settings::setCameraFront_image_roi_c_y0(QString value)
{
    setValue(rdth_image_roi_camera_front_c_y0_position, value);
    sync();
}

void settings::setCameraFront_image_roi_c_x1(QString value)
{
    setValue(rdth_image_roi_camera_front_c_x1_position, value);
    sync();
}

void settings::setCameraFront_image_roi_c_y1(QString value)
{
    setValue(rdth_image_roi_camera_front_c_y1_position, value);
    sync();
}

void settings::setCameraFront_image_roi_c_x2(QString value)
{
    setValue(rdth_image_roi_camera_front_c_x2_position, value);
    sync();
}

void settings::setCameraFront_image_roi_c_y2(QString value)
{
    setValue(rdth_image_roi_camera_front_c_y2_position, value);
    sync();
}

void settings::setCameraFront_image_roi_c_x3(QString value)
{
    setValue(rdth_image_roi_camera_front_c_x3_position, value);
    sync();
}

void settings::setCameraFront_image_roi_c_y3(QString value)
{
    setValue(rdth_image_roi_camera_front_c_y3_position, value);
    sync();
}

void settings::setCameraLeft_image_roi_c_x0(QString value)
{
    setValue(rdth_image_roi_camera_left_c_x0_position, value);
    sync();
}

void settings::setCameraLeft_image_roi_c_y0(QString value)
{
    setValue(rdth_image_roi_camera_left_c_y0_position, value);
    sync();
}

void settings::setCameraLeft_image_roi_c_x1(QString value)
{
    setValue(rdth_image_roi_camera_left_c_x1_position, value);
    sync();
}

void settings::setCameraLeft_image_roi_c_y1(QString value)
{
    setValue(rdth_image_roi_camera_left_c_y1_position, value);
    sync();
}

void settings::setCameraLeft_image_roi_c_x2(QString value)
{
    setValue(rdth_image_roi_camera_left_c_x2_position, value);
    sync();
}

void settings::setCameraLeft_image_roi_c_y2(QString value)
{
    setValue(rdth_image_roi_camera_left_c_y2_position, value);
    sync();
}

void settings::setCameraLeft_image_roi_c_x3(QString value)
{
    setValue(rdth_image_roi_camera_left_c_x3_position, value);
    sync();
}

void settings::setCameraLeft_image_roi_c_y3(QString value)
{
    setValue(rdth_image_roi_camera_left_c_y3_position, value);
    sync();
}

void settings::setCameraRight_image_roi_c_x0(QString value)
{
    setValue(rdth_image_roi_camera_right_c_x0_position, value);
    sync();
}

void settings::setCameraRight_image_roi_c_y0(QString value)
{
    setValue(rdth_image_roi_camera_right_c_y0_position, value);
    sync();
}

void settings::setCameraRight_image_roi_c_x1(QString value)
{
    setValue(rdth_image_roi_camera_right_c_x1_position, value);
    sync();
}

void settings::setCameraRight_image_roi_c_y1(QString value)
{
    setValue(rdth_image_roi_camera_right_c_y1_position, value);
    sync();
}

void settings::setCameraRight_image_roi_c_x2(QString value)
{
    setValue(rdth_image_roi_camera_right_c_x2_position, value);
    sync();
}

void settings::setCameraRight_image_roi_c_y2(QString value)
{
    setValue(rdth_image_roi_camera_right_c_y2_position, value);
    sync();
}

void settings::setCameraRight_image_roi_c_x3(QString value)
{
    setValue(rdth_image_roi_camera_right_c_x3_position, value);
    sync();
}

void settings::setCameraRight_image_roi_c_y3(QString value)
{
    setValue(rdth_image_roi_camera_right_c_y3_position, value);
    sync();
}

void settings::setCameraRear_image_roi_c_x0(QString value)
{
    setValue(rdth_image_roi_camera_rear_c_x0_position, value);
    sync();
}

void settings::setCameraRear_image_roi_c_y0(QString value)
{
    setValue(rdth_image_roi_camera_rear_c_y0_position, value);
    sync();
}

void settings::setCameraRear_image_roi_c_x1(QString value)
{
    setValue(rdth_image_roi_camera_rear_c_x1_position, value);
    sync();
}

void settings::setCameraRear_image_roi_c_y1(QString value)
{
    setValue(rdth_image_roi_camera_rear_c_y1_position, value);
    sync();
}

void settings::setCameraRear_image_roi_c_x2(QString value)
{
    setValue(rdth_image_roi_camera_rear_c_x2_position, value);
    sync();
}

void settings::setCameraRear_image_roi_c_y2(QString value)
{
    setValue(rdth_image_roi_camera_rear_c_y2_position, value);
    sync();
}

void settings::setCameraRear_image_roi_c_x3(QString value)
{
    setValue(rdth_image_roi_camera_rear_c_x3_position, value);
    sync();
}

void settings::setCameraRear_image_roi_c_y3(QString value)
{
    setValue(rdth_image_roi_camera_rear_c_y3_position, value);
    sync();
}
