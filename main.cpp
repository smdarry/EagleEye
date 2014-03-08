#include "camerawindow.h"
#include <QApplication>
#include <QDebug>

#include "videosource.h"
#include "opencv2/core/core.hpp"

using namespace cv;

int main(int argc, char *argv[])
{
    VideoSource videoSrc;
    videoSrc.init();

    QApplication a(argc, argv);
    CameraWindow w;
    w.show();

    videoSrc.addPushListener(w);
    videoSrc.start();

    return a.exec();
}
