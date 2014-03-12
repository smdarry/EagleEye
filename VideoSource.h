#ifndef VIDEOSOURCE_H
#define VIDEOSOURCE_H

#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>

#include <QWidget>

using namespace cv;

class VideoSource : public QObject
{
    Q_OBJECT
private:
    VideoCapture* _camera;

public:
    VideoSource();
    virtual ~VideoSource();

    void init();
    void start();

protected:
    void timerEvent(QTimerEvent *);

signals:
    void pushRawFrame(Mat&);
};

#endif // VIDEOSOURCE_H
