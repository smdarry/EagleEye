#ifndef CAMERAWINDOW_H
#define CAMERAWINDOW_H

#include <QWidget>

#include "QOpenCVWidget.h"
#include "videosource.h"

#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>

class CameraWindow : public QWidget, public PushVideoListener
{
    Q_OBJECT
private:
    QOpenCVWidget* _cvwidget;

public:
    explicit CameraWindow(QWidget *parent = 0);
    virtual void onPush(Mat& buffer);

signals:

public slots:

};

#endif // CAMERAWINDOW_H
