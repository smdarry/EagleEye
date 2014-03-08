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
    TextDetectElement textDetect;

    videoSrc.addPushListener(cannyFilter);
    cannyFilter.addPushListener(textDetect);
    textDetect.addPushListener(w);

    videoSrc.start();

    return a.exec();
}
