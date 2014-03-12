#ifndef CAMERAWINDOW_H
#define CAMERAWINDOW_H

#include <QWidget>

#include "QOpenCVWidget.h"
#include "videosource.h"

#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>

using namespace cv;

class CameraWindow : public QWidget
{
    Q_OBJECT
private:
    QOpenCVWidget* _cvwidget;

public:
    explicit CameraWindow(QWidget *parent = 0);

signals:

public slots:
    void onPushImage(Mat&);
};

#endif // CAMERAWINDOW_H
