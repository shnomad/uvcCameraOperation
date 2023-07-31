#ifndef IMAGE_POST_PROCESS_H
#define IMAGE_POST_PROCESS_H

#include <QObject>
#include "image_warp_perspective.h"
#include "image_concat.h"

class image_post_process : public QObject
{
    Q_OBJECT
public:
    explicit image_post_process(QObject *parent = nullptr);
    ~image_post_process();

signals:
    void sig_image_concat_working();

public slots:
    void image_roi_concat();

private:
    imageWarpPerspective *m_imageWarp;
    image_concat *m_image_concat;

    /*JPEG Image Buffer*/
    QVector<Mat> warpedImage;
//  QVector<QString> imageNameBuffer;

    /*temporary geometry*/
    int x0=108, x1=523, x2=87, x3=561, y0=204, y1=194, y2=391, y3=308;
};

#endif // IMAGE_POST_PROCESS_H
