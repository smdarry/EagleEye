#include "camerawindow.h"
#include <QDebug>

CameraWindow::CameraWindow(QWidget *parent) :
    QWidget(parent)
{
    _cvwidget = new QOpenCVWidget(this);

    QVBoxLayout *mainLayout = new QVBoxLayout;
    mainLayout->addWidget(_cvwidget);
    setLayout(mainLayout);

    resize(500, 400);
}

void CameraWindow::onPushImage(Mat &image)
{
    _cvwidget->putImage(image);
}
