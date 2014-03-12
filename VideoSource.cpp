#include "videosource.h"

#include <QDebug>

VideoSource::VideoSource()
{
}

VideoSource::~VideoSource()
{
    delete _camera;
}

void VideoSource::init()
{
    _camera = new VideoCapture(0);
    if(!_camera->isOpened())
    {
        qDebug() << "Could not open video capture device" << endl;
        return;
    }
}

void VideoSource::start()
{
    startTimer(100);
}

void VideoSource::timerEvent(QTimerEvent *)
{
    Mat frame;
    _camera->read(frame);

//    notify(frame);

    emit pushRawFrame(frame);
}
