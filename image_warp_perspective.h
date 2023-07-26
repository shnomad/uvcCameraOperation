#ifndef WARPPERSPECTIVE_TEST_H
#define WARPPERSPECTIVE_TEST_H

#include <QObject>
//#include <QLabel>
#include <QTimer>
#include <iostream>
#include <QMutex>
#include "image_concat.h"
//#include <windows.h>
//#include "opencv2/imgproc.hpp"
//#include "opencv2/imgcodecs.hpp"
//#include "opencv2/highgui.hpp"

//using namespace std;
//using namespace cv;

class imageWarpPerspective : public QObject
{
    Q_OBJECT

public:
      explicit imageWarpPerspective(quint8,QObject *parent = nullptr);
    ~imageWarpPerspective();

    void imageWarp(int, int, int, int, int, int, int, int, int, QString, Mat, bool);

signals:
//    void sig_image_concat(bool);
      void sig_image_concat(quint8);
      void sig_image_concat_buf_0();
      void sig_image_concat_buf_1();
      void sig_image_concat_buf_2();

public slots:
      void check_image_warped_buffer_empty(int);

private:

    QVector<Mat> warped_iamge_file_buffer_0, warped_iamge_file_buffer_1, warped_iamge_file_buffer_2;
    QVector<QString> warped_image_file_name_buffer_0, warped_image_file_name_buffer_1, warped_image_file_name_buffer_2;

    bool is_buffer0_concat = false;

//  QTimer *img_concat_timer;
    image_concat *m_image_concat;
    QMutex buf0_mutex, buf1_mutex, buf2_mutex;
    volatile quint64 image_warped_count = 0;
    quint8 thread_ch;

    bool iswarpedbuffe_0_empty = false, iswarpedbuffe_1_empty = false, iswarpedbuffe_2_empty = false;

};

#endif // WARPPERSPECTIVE_TEST_H
