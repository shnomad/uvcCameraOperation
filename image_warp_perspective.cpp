
//#include <QImage>
#include <QFile>
#include "image_warp_perspective.h"
#include "common.h"

imageWarpPerspective::imageWarpPerspective(quint8 th_ch, QObject *parent) : QObject(parent)
{
      thread_ch = th_ch;
      m_image_concat = new image_concat;

    connect(this, &imageWarpPerspective::sig_image_concat_buf_0, [&]()
    {
        if(!warped_iamge_file_buffer_0.empty() && !warped_image_file_name_buffer_0.empty())
        {

          QString concat_image_start, concat_image_last;

          Log()<<"thread_ch :" <<thread_ch <<", buffer 0 image concat ";

          buf0_mutex.lock();

          concat_image_start = warped_image_file_name_buffer_0.last();
          concat_image_start.chop(5);
          concat_image_last = warped_image_file_name_buffer_0.front().section("/",-1);

          Log()<<"concat_image_start:"<<concat_image_start;
          Log()<<"concat_image_last :"<<concat_image_last;

          Log()<<"warped_iamge_file_buffer_0.length() :"<<warped_iamge_file_buffer_0.length();

          m_image_concat->createOne(warped_iamge_file_buffer_0,1,0,concat_image_start +"_"+ concat_image_last);

          Log()<<"image concat complete";

          //capture_image_file_name_buffer_0.erase(capture_image_file_name_buffer_0.begin()

          warped_iamge_file_buffer_0.clear();
          warped_image_file_name_buffer_0.clear();

          buf0_mutex.unlock();
        }
    });

    connect(this, &imageWarpPerspective::sig_image_concat_buf_1, [&]()
    {
        if(!warped_iamge_file_buffer_1.empty() && !warped_image_file_name_buffer_1.empty())
        {

          QString concat_image_start, concat_image_last;

          Log()<<"thread_ch :" <<thread_ch <<", buffer 1 image concat ";

          buf1_mutex.lock();

          concat_image_start = warped_image_file_name_buffer_1.last();
          concat_image_start.chop(5);
          concat_image_last = warped_image_file_name_buffer_1.front().section("/",-1);

          Log()<<"concat_image_start:"<<concat_image_start;
          Log()<<"concat_image_last :"<<concat_image_last;

          Log()<<"warped_iamge_file_buffer_1.length() :"<<warped_iamge_file_buffer_0.length();

          m_image_concat->createOne(warped_iamge_file_buffer_1,1,0,concat_image_start +"_"+ concat_image_last);

          Log()<<"image concat complete";

          warped_iamge_file_buffer_1.clear();
          warped_image_file_name_buffer_1.clear();

          buf1_mutex.unlock();
        }
    });

    connect(this, &imageWarpPerspective::sig_image_concat_buf_2, [&]()
    {
        if(!warped_iamge_file_buffer_2.empty() && !warped_image_file_name_buffer_2.empty())
        {

          QString concat_image_start, concat_image_last;

          Log()<<"thread_ch :" <<thread_ch <<", buffer 2 image concat ";

          buf2_mutex.lock();

          concat_image_start = warped_image_file_name_buffer_2.last();
          concat_image_start.chop(5);
          concat_image_last = warped_image_file_name_buffer_2.front().section("/",-1);

          Log()<<"concat_image_start:"<<concat_image_start;
          Log()<<"concat_image_last :"<<concat_image_last;

          Log()<<"warped_iamge_file_buffer_2.length() :"<<warped_iamge_file_buffer_0.length();

           m_image_concat->createOne(warped_iamge_file_buffer_2,1,0,concat_image_start +"_"+ concat_image_last);

           Log()<<"image concat complete";

          warped_iamge_file_buffer_2.clear();
          warped_image_file_name_buffer_2.clear();

          buf2_mutex.unlock();
        }
    });


}

imageWarpPerspective::~imageWarpPerspective()
{
      delete m_image_concat;
}

void imageWarpPerspective::imageWarp(int x0, int y0, int x1, int y1, int x2, int y2, int x3, int y3, int ratio,\
                                     QString name, Mat original_img, bool input_caption)
{
    QMutex mutex;

    QString input_text = name.section("/", -1);
    QByteArray input_n = input_text.toLocal8Bit();
    char *chrTest_input = input_n.data();

    vector<Point2f> corners(4);

    corners[0]=Point2f(x0*ratio, y0*ratio);
    corners[1]=Point2f(x1*ratio, y1*ratio);
    corners[2]=Point2f(x2*ratio, y2*ratio);
    corners[3]=Point2f(x3*ratio, y3*ratio);

#if 1
    quint32 img_length=0, img_height=0;

    if(x1-x0<x3-x2)
        img_length = x3-x2;
    else
        img_length = x1-x0;

    Log()<<"img_length :"<<img_length;

    if(y2-y0<y3-y1)
        img_height = y3-y1;
    else
        img_height = y2-y0;

    Log()<<"img_height :"<<img_height;

    if(img_length%4)
    {
        img_length = (img_length + (4-1)) & ~(4-1);
    }

    Log()<<"img_length_recal :"<<img_length;

    if(img_height%4)
    {
        img_height = (img_height + (4-1)) & ~(4-1);
    }

    Log()<<"img_height_recal :"<<img_height;

     Size warpSize(img_length*ratio, img_height*ratio);

     Mat warpImg(warpSize, original_img.type());

     vector<Point2f> warpCorners(4);

     warpCorners[0]=Point2f(0, 0);
     warpCorners[1]=Point2f(img_length*ratio, 0);                       //length
     warpCorners[2]=Point2f(0, img_height*ratio);                       //height
     warpCorners[3]=Point2f(img_length*ratio, img_height*ratio);        //length x height

#else
    Size warpSize(original_img.cols, original_img.rows);

    Mat warpImg(warpSize, original_img.type());

    vector<Point2f> warpCorners(4);

    warpCorners[0]=Point2f(0, 0);
    warpCorners[1]=Point2f(warpImg.cols, 0);
    warpCorners[2]=Point2f(0, warpImg.rows);
    warpCorners[3]=Point2f(warpImg.cols, warpImg.rows);

#endif

    Mat trans= getPerspectiveTransform(corners, warpCorners);    

   /* Image Warping */
    Log()<<name;

    QByteArray n_name = name.toLocal8Bit();
    char *chrTest = n_name.data();

    warpPerspective(original_img, warpImg, trans, warpSize);     //output : warpImg

    /*Input Text informaion to warped Image*/
    if(input_caption)
        putText(warpImg, chrTest_input, Point(200, 1900),1, 10, Scalar(0, 128, 255), 3, 8);    

//  imwrite(chrTest, warpImg);

    /*Warped Image save to Vetor list*/

    Log()<<"thread_ch "<<thread_ch <<" image_warped_count :"<<image_warped_count;

    if(image_warped_count <10)
    {
        buf0_mutex.lock();

        warped_iamge_file_buffer_0.push_front(warpImg);
        warped_image_file_name_buffer_0.push_front(name);

        buf0_mutex.unlock();

        image_warped_count++;

        Log()<<"warped_iamge_file_buffer_0.length() :"<<warped_iamge_file_buffer_0.length();

        if(warped_iamge_file_buffer_0.length() == 10)
        {
           emit sig_image_concat_buf_0();
        }
    }
    else if(image_warped_count > 9 && image_warped_count < 20)
    {
        buf1_mutex.lock();

        warped_iamge_file_buffer_1.push_front(warpImg);
        warped_image_file_name_buffer_1.push_front(name);

        buf1_mutex.unlock();

        image_warped_count++;

        Log()<<"warped_iamge_file_buffer_1.length() :"<<warped_iamge_file_buffer_1.length();

        if(warped_iamge_file_buffer_1.length() == 10)
        {
            emit sig_image_concat_buf_1();
        }
    }
    else if(image_warped_count > 19 && image_warped_count < 30)
    {
        buf2_mutex.lock();

        warped_iamge_file_buffer_2.push_front(warpImg);
        warped_image_file_name_buffer_2.push_front(name);

        buf2_mutex.unlock();

        image_warped_count++;

        Log()<<"warped_iamge_file_buffer_2.length() :"<<warped_iamge_file_buffer_2.length();

        if(warped_iamge_file_buffer_2.length() == 10)
        {
            emit sig_image_concat_buf_2();
            image_warped_count=0;
        }
    }
}

void imageWarpPerspective::check_image_warped_buffer_empty(int buffer)
{

    switch(buffer)
    {
        case 0:

        Log();
        iswarpedbuffe_0_empty = true;

        break;

        case 1:

        Log();
        iswarpedbuffe_1_empty = true;

        break;

        case 2:

        Log();
        iswarpedbuffe_2_empty = true;

        break;
    }

    if(iswarpedbuffe_0_empty && iswarpedbuffe_1_empty && iswarpedbuffe_2_empty)
    {
        Log();

        emit sig_image_concat_buf_0();
        emit sig_image_concat_buf_1();
        emit sig_image_concat_buf_2();

        iswarpedbuffe_0_empty = false;
        iswarpedbuffe_1_empty = false;
        iswarpedbuffe_2_empty = false;

        image_warped_count =0;
    }

}
