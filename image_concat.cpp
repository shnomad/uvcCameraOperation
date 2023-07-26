#include "image_concat.h"
#include "common.h"

image_concat::image_concat(QObject *parent) : QObject(parent)
{
#if 0
    Log()<<"image_concat channel :" << ch <<" Thread started";

    img_concat_timer_0 = new QTimer(this);
    img_concat_timer_1 = new QTimer(this);
    img_concat_timer_2 = new QTimer(this);

    img_concat_timer_0->setSingleShot(true);
    img_concat_timer_1->setSingleShot(true);
    img_concat_timer_2->setSingleShot(true);

    connect(img_concat_timer_0, &QTimer::timeout,this,[this]
    {
        if(!warped_img_0.empty())
        {
            Log();

            createOne(warped_img_0, 1, 0);

            Log();
            Log();
        }
    });

    connect(img_concat_timer_1, &QTimer::timeout,this,[this]
    {
        if(!warped_img_1.empty())
        {
            createOne(warped_img_1, 1, 0);
        }
    });

    connect(img_concat_timer_2, &QTimer::timeout,this,[this]
    {
        if(!warped_img_2.empty())
        {
            createOne(warped_img_2, 1, 0);
        }
    });
#endif
}

image_concat::~image_concat()
{

}

void image_concat::receive_warped_img_vector(QVector<Mat> img_vector, quint8 img_vector_number,bool survey_complete)
{
#if 0
    Log()<<"img_cnt :"<<img_vector.size();
    Log()<<"img_vector_number :"<<img_vector_number;
    Log()<<"survey_complete :" <<survey_complete;

    if(img_vector_number==0)
    {
        warped_img_0 = img_vector;
        img_concat_timer_0->start(10);
    }
    else if(img_vector_number==1)
    {
        warped_img_1 = img_vector;
        img_concat_timer_1->start(10);
    }
     else if(img_vector_number==2)
    {
        warped_img_2 = img_vector;
        img_concat_timer_2->start(10);
    }
#endif
}

Mat image_concat::createOne(QVector<cv::Mat> & images, int cols, int min_gap_size, QString filename)
{
        // let's first find out the maximum dimensions
        int max_width = 0;
        int max_height = 0;

        for (int i = 0; i < images.size(); i++)
        {
            // check if type is correct
            // you could actually remove that check and convert the image
            // in question to a specific type
            if ( i > 0 && images[i].type() != images[i-1].type() )
            {
                std::cerr << "WARNING:createOne failed, different types of images";
                return cv::Mat();
            }

            max_height = std::max(max_height, images[i].rows);
            max_width = std::max(max_width, images[i].cols);
        }
        // number of images in y direction
        int rows = std::ceil(images.size() / (float)cols);

        // create our result-matrix
        cv::Mat result = cv::Mat::zeros(rows*max_height + (rows-1)*min_gap_size,
                                        cols*max_width + (cols-1)*min_gap_size, images[0].type());
        size_t i = 0;
        int current_height = 0;
        int current_width = 0;

        for ( int y = 0; y < rows; y++ )
        {
            for ( int x = 0; x < cols; x++ )
            {
                if (i >= images.size()) // shouldn't happen, but let's be safe
                    return result;

                // get the ROI in our result-image
                cv::Mat to(result,
                           cv::Range(current_height, current_height + images[i].rows),
                           cv::Range(current_width, current_width + images[i].cols));
                // copy the current image to the ROI
                images[i++].copyTo(to);

                current_width += max_width + min_gap_size;
            }

            // next line - reset width and update height
            current_width = 0;
            current_height += max_height + min_gap_size;
        }

        /*work around for Korean language*/
         QByteArray input_n = filename.toLocal8Bit();
         char *chrTest_input = input_n.data();

         imwrite(chrTest_input,result);

//       imwrite(filename.toStdString(),result);

        return result;
}
