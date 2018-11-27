#include "evgui.h"
#include "ui_evgui.h"
#include <QPalette>

EVgui::EVgui(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::EVgui)
{
    ui->setupUi(this);

    clk.start(10);
    QObject::connect(&clk, SIGNAL(timeout()), this, SLOT(start()));
    QObject::connect(&clk, SIGNAL(timeout()), this, SLOT(process()));

}

EVgui::~EVgui()
{
    delete ui;
}


//
VideoCapture capture(0);
void EVgui::start()
{
     capture >> image;
     //Mat image1;
     //cvtColor(image,image1,CV_BGR2RGB);
     if(image==NULL)
     {
         cout<<"please insert camera!!"<<endl;
     }
     else
     {
         QImage show_image = QImage((const unsigned char*)image.data, image.cols, image.rows, image.cols* image.channels(), QImage::Format_RGB888).rgbSwapped();
         ui->pic->setPixmap(QPixmap::fromImage(show_image));
     }


}

///////////txt
void EVgui::process()
{
    pro_img=image.clone();
    int img_R;
    int img_G;
    int img_B;
    int sum_R;
    int sum_G;
    int sum_B;
    for(int i=0;i<image.rows;i++)
    {
        for(int j=0;j<image.cols;j++)
        {
            img_R=image.at<Vec3b>(i,j)[2];
            sum_R+=img_R;
            img_G=image.at<Vec3b>(i,j)[1];
            sum_G+=img_G;
            img_B=image.at<Vec3b>(i,j)[0];
            sum_B+=img_B;
        }
    }
    int sum = sum_R + sum_G + sum_B;

    int imgSize=image.rows*image.cols;
    float avg_R=0.0;
    avg_R= sum_R/imgSize;
    float avg_G=0.0;
    avg_G= sum_G/imgSize;
    float avg_B=0.0;
    avg_B= sum_B/imgSize;

    float coef_R = sum_R/sum;
    float coef_G = sum_G/sum;
    float coef_B = sum_B/sum;



    for(int i=0;i<image.rows;i++)
    {
        for(int j=0;j<image.cols;j++)
        {
            img_R=image.at<Vec3b>(i,j)[2];
            img_G=image.at<Vec3b>(i,j)[1];
            img_B=image.at<Vec3b>(i,j)[0];
            //

            float decR;
            float decG;
            float decB;

            decR=(img_R-avg_R)*(img_R-avg_R);
            decG=(img_G-avg_G)*(img_G-avg_G);
            decB=(img_B-avg_B)*(img_B-avg_B);

            float dec_R = sqrt(decR)/imgSize;
            float dec_G = sqrt(decG)/imgSize;
            float dec_B = sqrt(decB)/imgSize;

            float dist_R = abs(img_R-avg_R);
            float dist_G = abs(img_G-avg_G);
            float dist_B = abs(img_B-avg_B);

            int R = (dist_R > dec_R)&(img_R > avg_R);
            int G = (dist_G > dec_G)&(img_G > avg_G);
            int B = (dist_B > dec_B)&(img_B > avg_B);
            float inv_R;
            float inv_G;
            float inv_B;
            if(R)
            {

                inv_R = img_R*(coef_R+1);
            }
            else
            {
                inv_R =img_R*coef_R;
            }
            if(G)
            {

                inv_G = img_G*(coef_G+1);
            }
            else
            {
                inv_G =img_G*coef_G;
            }
            if(B)
            {

                inv_B = img_B*(coef_B+1);
            }
            else
            {
                inv_B =img_B*coef_B;
            }

            Vec3b pixel;
            pixel[2]=inv_R*0.299;
            pixel[1]=inv_G*0.587;
            pixel[0]=inv_B*0.114;
            pro_img.at<Vec3b>(i,j)=pixel;
        }
    }
    //imshow("dstimg",image);


    cvtColor(pro_img,grayImage,CV_RGB2GRAY);



    threshold (grayImage,dstImage,0,255,THRESH_OTSU);

    int imgsize=dstImage.rows*dstImage.cols;
    float ratio=bSums(dstImage)*100/imgsize;
    //cout<<ratio<<"%"<<endl;
    QFont ft;
    ft.setPointSize(10);
    ui->label_9->setFont(ft);
    QFont ft1;
    ft1.setPointSize(12);
    ui->label_10->setFont(ft1);

    ui->ratio->setText(QString::number(ratio));
    //sauvola(grayImage.data,dstImage.data,grayImage.cols,grayImage.rows,0.065,3);

    QImage iGray((const unsigned char*)(dstImage.data),dstImage.cols,dstImage.rows,QImage::Format_Indexed8);
    ui->pic1->setPixmap(QPixmap::fromImage(iGray));

}

int EVgui::bSums(Mat src)
{

    int counter = 0;
    //迭代器访问像素点
    Mat_<uchar>::iterator it = src.begin<uchar>();
    Mat_<uchar>::iterator itend = src.end<uchar>();
    for (; it!=itend; ++it)
    {
        if((*it)>0) counter+=1;//二值化后，像素点是0或者255
    }
    return counter;
}

