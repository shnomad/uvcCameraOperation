#ifndef SETTINGS_H
#define SETTINGS_H

#include <QObject>
#include <QSettings>
#include <QTextStream>
#include "setting_flagname_definition.h"

class settings : public QSettings
{
    Q_OBJECT
public:
    explicit settings(QObject *parent = nullptr);
    ~settings();

    static settings *Instance();
    const QHash<QString, QVariant> getSettings();
    void setSettings(const QHash<QString, QVariant> &settingValue);

    bool getSurveySet();
    QString getSurveyName();    
    QString getSurveyPerson();
    QString getSurveyRoutine();
    QString getSurveyRoad();

    QString getSurveyDirection();
    QString getSurveyDirectionDetail();
    QString getSurveyResultStorageLocation();

    QString getCameraFront_Description();
    QString getCameraLeft_Description();
    QString getCameraRight_Description();
    QString getCameraRear_Description();
    QString getCameraAroundView_Description();

    QString getCameraFront_DevicePath();
    QString getCameraLeft_DevicePath();
    QString getCameraRight_DevicePath();
    QString getCameraRear_DevicePath();
    QString getCameraAroundView_DevicePath();

    uint getCameraFront_trigger_interval();
    uint getCameraLeft_trigger_interval();
    uint getCameraRight_trigger_interval();
    uint getCameraRear_trigger_interval();

    QString getDMI_Information();
    QString getGPS_Information();

    bool getIsDMIused();
    bool getIsGPSused();

    quint32 getDMIinterval();

    quint32 getCameraCh5_captureMode();

    quint8 getCameraFront_resolution();
    quint8 getCameraLeft_resolution();
    quint8 getCameraRight_resolution();
    quint8 getCameraRear_resolution();

    QString getCameraFront_userInput();
    QString getCameraLeft_userInput();
    QString getCameraRight_userInput();
    QString getCameraRear_userInput();

    QString getCameraFront_image_roi_c_x0();
    QString getCameraFront_image_roi_c_y0();
    QString getCameraFront_image_roi_c_x1();
    QString getCameraFront_image_roi_c_y1();
    QString getCameraFront_image_roi_c_x2();
    QString getCameraFront_image_roi_c_y2();
    QString getCameraFront_image_roi_c_x3();
    QString getCameraFront_image_roi_c_y3();

    QString getCameraLeft_image_roi_c_x0();
    QString getCameraLeft_image_roi_c_y0();
    QString getCameraLeft_image_roi_c_x1();
    QString getCameraLeft_image_roi_c_y1();
    QString getCameraLeft_image_roi_c_x2();
    QString getCameraLeft_image_roi_c_y2();
    QString getCameraLeft_image_roi_c_x3();
    QString getCameraLeft_image_roi_c_y3();

    QString getCameraRight_image_roi_c_x0();
    QString getCameraRight_image_roi_c_y0();
    QString getCameraRight_image_roi_c_x1();
    QString getCameraRight_image_roi_c_y1();
    QString getCameraRight_image_roi_c_x2();
    QString getCameraRight_image_roi_c_y2();
    QString getCameraRight_image_roi_c_x3();
    QString getCameraRight_image_roi_c_y3();

    QString getCameraRear_image_roi_c_x0();
    QString getCameraRear_image_roi_c_y0();
    QString getCameraRear_image_roi_c_x1();
    QString getCameraRear_image_roi_c_y1();
    QString getCameraRear_image_roi_c_x2();
    QString getCameraRear_image_roi_c_y2();
    QString getCameraRear_image_roi_c_x3();
    QString getCameraRear_image_roi_c_y3();

    void setSurveySet(bool);
    void setSurveyName(QString);
    void setSurveyPerson(QString);
    void setSurveyRoutine(QString);
    void setSurveyRoad(QString);

    void setSurveyDirection(QString);
    void setSurveyDirectionDetail(QString);
    void setSurveyResultStorageLocation(QString);

    void setDMI_Information(QString);
    void setGPS_Information(QString);

    void setIsDMI_use(bool);
    void setIsGPS_use(bool);

    void setDMIinterval(int);

    void setCameraFront_Description(QString);
    void setCameraLeft_Description(QString);
    void setCameraRight_Description(QString);
    void setCameraRear_Description(QString);
    void setCameraAroundView_Description(QString);

    void setCameraFront_DevicePath(QString);
    void setCameraLeft_DevicePath(QString);
    void setCameraRight_DevicePath(QString);
    void setCameraRear_DevicePath(QString);
    void setCameraAroundView_DevicePath(QString);

    void setCameraFront_trigger_interval(uint);
    void setCameraLeft_trigger_interval(uint);
    void setCameraRight_trigger_interval(uint);
    void setCameraRear_trigger_interval(uint);

    void setCameraFront_resolution(QString);
    void setCameraLeft_resolution(QString);
    void setCameraRight_resolution(QString);
    void setCameraRear_resolution(QString);

    void setCameraFront_userInput(QString);
    void setCameraLeft_userInput(QString);
    void setCameraRight_userInput(QString);
    void setCameraRear_userInput(QString);

    void setCameraCh5_captureMode(quint32);

    void setCameraFront_image_roi_c_x0(QString);
    void setCameraFront_image_roi_c_y0(QString);
    void setCameraFront_image_roi_c_x1(QString);
    void setCameraFront_image_roi_c_y1(QString);
    void setCameraFront_image_roi_c_x2(QString);
    void setCameraFront_image_roi_c_y2(QString);
    void setCameraFront_image_roi_c_x3(QString);
    void setCameraFront_image_roi_c_y3(QString);

    void setCameraLeft_image_roi_c_x0(QString);
    void setCameraLeft_image_roi_c_y0(QString);
    void setCameraLeft_image_roi_c_x1(QString);
    void setCameraLeft_image_roi_c_y1(QString);
    void setCameraLeft_image_roi_c_x2(QString);
    void setCameraLeft_image_roi_c_y2(QString);
    void setCameraLeft_image_roi_c_x3(QString);
    void setCameraLeft_image_roi_c_y3(QString);

    void setCameraRight_image_roi_c_x0(QString);
    void setCameraRight_image_roi_c_y0(QString);
    void setCameraRight_image_roi_c_x1(QString);
    void setCameraRight_image_roi_c_y1(QString);
    void setCameraRight_image_roi_c_x2(QString);
    void setCameraRight_image_roi_c_y2(QString);
    void setCameraRight_image_roi_c_x3(QString);
    void setCameraRight_image_roi_c_y3(QString);

    void setCameraRear_image_roi_c_x0(QString);
    void setCameraRear_image_roi_c_y0(QString);
    void setCameraRear_image_roi_c_x1(QString);
    void setCameraRear_image_roi_c_y1(QString);
    void setCameraRear_image_roi_c_x2(QString);
    void setCameraRear_image_roi_c_y2(QString);
    void setCameraRear_image_roi_c_x3(QString);
    void setCameraRear_image_roi_c_y3(QString);

signals:

private:
    QString getAppPath();

};

#endif // SETTINGS_H
