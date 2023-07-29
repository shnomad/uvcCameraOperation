#include <QFile>
#include <QImageReader>
#include "image_post_process.h"
#include "common.h"

image_post_process::image_post_process(QObject *parent) : QObject(parent)
{
    Log()<<"Image Post Process Thread Started!!";
    m_imageWarp = new imageWarpPerspective;
    m_image_concat = new image_concat;

   connect(this, &image_post_process::sig_image_concat_working, this, [this]()
   {

   });
}

image_post_process::~image_post_process()
{

}

void  image_post_process::read_image(const QByteArray &img, QString filename)
{
/*
    QFile file(file_name);

    if (file.open(QIODevice::WriteOnly))
    {
       file.write(img);
       file.close();
    }
*/
    Log()<<"JPG converting to Mat Start";
    Mat img_tmp = imdecode(vector<char>(img.begin(), img.end()), IMREAD_ANYCOLOR);
    Log()<<"JPG converting to Mat end";
//  imwrite(file_name.toStdString(), img_tmp);
}
