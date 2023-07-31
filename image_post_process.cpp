#include <QFile>
#include <QImageReader>
#include "image_post_process.h"
#include "common.h"
#include "global.h"

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

void image_post_process::image_roi_concat()
{
    Log()<<"image convert to Mat start";
    do
    {
        warpedImage.push_back(imdecode(vector<char>(global.jpg_file_buffer_0.front().begin(), global.jpg_file_buffer_0.front().end()), IMREAD_ANYCOLOR));

        global.jpg_file_buffer_0.erase(global.jpg_file_buffer_0.begin());

        Log()<<"global.jpg_file_buffer_0.length() :"<<global.jpg_file_buffer_0.length();

    }while(!global.jpg_file_buffer_0.empty());

    Log()<<"image convert to Mat end";
}

#if 0
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
}
#endif
