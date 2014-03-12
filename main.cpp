#include "camerawindow.h"
#include <QApplication>
#include <QDebug>

#include "VideoSource.h"
#include "CannyFilter.h"
#include "TextDetectElement.h"

#include "opencv2/core/core.hpp"

using namespace cv;

int main(int argc, char *argv[])
{
    VideoSource videoSrc;
    videoSrc.init();

    QApplication a(argc, argv);
    CameraWindow w;
    w.show();

    CannyFilter cannyFilter;
    cannyFilter.setLowThreshold(50);
    cannyFilter.setHighThreshold(100);
    TextDetectElement textDetect;

    QObject::connect(&videoSrc, SIGNAL(pushRawFrame(Mat&)), &cannyFilter, SLOT(onPushRawFrame(Mat&)));
    QObject::connect(&videoSrc, SIGNAL(pushRawFrame(Mat&)), &textDetect, SLOT(onPushRawFrame(Mat&)));
    QObject::connect(&cannyFilter, SIGNAL(pushEdgeImage(Mat&)), &textDetect, SLOT(onPushEdgeImage(Mat&)));
    QObject::connect(&textDetect, SIGNAL(pushResultImage(Mat&)), &w, SLOT(onPushImage(Mat&)));

//    videoSrc.addPushListener(cannyFilter);
//    cannyFilter.addPushListener(textDetect);
//    textDetect.addPushListener(w);

    videoSrc.start();

    return a.exec();
}
