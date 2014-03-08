#ifndef VIDEOSOURCE_H
#define VIDEOSOURCE_H

#include "baseelement.h"

#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>

#include <QWidget>

using namespace cv;

typedef BaseElement<Mat>::PushListener PushVideoListener;

class VideoSource : public BaseElement<Mat>, public QObject
{
private:
    VideoCapture* _camera;

public:
    VideoSource();
    virtual ~VideoSource();

    void init();
    void start();

protected:
    void timerEvent(QTimerEvent *);
};

#endif // VIDEOSOURCE_H
