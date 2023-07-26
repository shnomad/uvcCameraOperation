#ifndef IMAGE_CONCAT_H
#define IMAGE_CONCAT_H

#include <QObject>
#include <QTimer>
#include <QVector>
#include <opencv2/opencv.hpp>

using namespace cv;
using namespace std;

class image_concat: public QObject
{
    Q_OBJECT
public:
 //   explicit image_concat(quint8, QObject *parent = nullptr);
      explicit image_concat(QObject *parent = nullptr);
    ~image_concat();

//   Mat createOne(QVector<cv::Mat> & images, int cols, int min_gap_size);
     Mat createOne(QVector<cv::Mat> & images, int cols, int min_gap_size, QString filename);
signals:

public slots:
    void receive_warped_img_vector(QVector<Mat>, quint8, bool);

private:
    QTimer *img_concat_timer_0, *img_concat_timer_1, *img_concat_timer_2;
    QVector<Mat> warped_img_0, warped_img_1, warped_img_2;

};

#endif // IMAGE_CONCAT_H
