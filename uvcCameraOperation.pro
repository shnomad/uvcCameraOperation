QT -= gui

QT += core network mqtt
CONFIG += c++11 console
CONFIG -= app_bundle

# The following define makes your compiler emit warnings if you use
# any Qt feature that has been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
        camerathread.cpp \
        cli_monitor.cpp \
        controller.cpp \
        deviceinfo.cpp \
#       display/display.c \
        display/ssd1306_i2c.c \
        jsondatahandle.cpp \
        main.cpp \
        mqtt.cpp \
        socketserver.cpp \
        sys_cmd_resp.cpp

HEADERS += \
    camerathread.h \
    cli_monitor.h \
    common.h \
    controller.h \
    deviceinfo.h \
    display/bmp.h \
    display/oled_fonts.h \
    display/ssd1306_i2c.h \
    jsondatahandle.h \
    mqtt.h \
    socketserver.h \
    sys_cmd_resp.h

INCLUDEPATH +=/opt/Rpi4-roadtech/sysroot/usr/local/include
INCLUDEPATH +=/opt/Rpi4-roadtech/sysroot/usr/local/lib/opencv-4.6.0/include/opencv4

LIBS += -L/opt/Rpi4-roadtech/sysroot/usr/local/lib/arm-linux-gnueabihf -luvc \
        -L/opt/Rpi4-roadtech/sysroot/usr/local/lib/opencv-4.6.0/lib \
         -lopencv_calib3d \
         -lopencv_core \
         -lopencv_features2d \
         -lopencv_flann \
         -lopencv_highgui \
         -lopencv_imgcodecs \
         -lopencv_imgproc \
         -lopencv_ml \
         -lopencv_dnn \
         -lopencv_objdetect \
         -lopencv_photo \
         -lopencv_shape \
         -lopencv_stitching \
         -lopencv_superres \
         -lopencv_video \
         -lopencv_videoio \
         -lopencv_videostab \
         -lopencv_optflow \
         -lopencv_ximgproc \
         -lopencv_xfeatures2d

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /home/rt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
