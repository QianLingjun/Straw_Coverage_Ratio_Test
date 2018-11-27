#ifndef EVGUI_H
#define EVGUI_H

#include <QCoreApplication>
#include <QMainWindow>
#include <QWidget>
#include <opencv2/opencv.hpp>
#include <QTimer>
#include <vector>
#include <iostream>
#include<cmath>
#include<iomanip>
#include "ui_evgui.h"
#include <QtCore/QTextStream>
#include <QtCore/QIODevice>
#include <qDebug>

using namespace std;
using namespace cv;


//图像处理参数

namespace Ui {
class EVgui;
}

class EVgui : public QMainWindow
{
    Q_OBJECT

public:
    explicit EVgui(QWidget *parent = 0);
    ~EVgui();
    Mat image;
    //Mat image1;
    Mat show_image;
    Mat pro_img;
    Mat iGray;
    Mat grayImage;
    Mat dstImage;

    QTimer clk;

    int bSums(Mat src);

private:
    Ui::EVgui *ui;

private slots:
    void start();
    void process();


};

#endif // EVGUI_H
