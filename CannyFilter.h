#ifndef CANNYFILTER_H
#define CANNYFILTER_H

#include "VideoSource.h"

using namespace cv;

class CannyFilter : public QObject
{
    Q_OBJECT

private:
    float _lowThreshold;
    float _highThreshold;

public:
    CannyFilter();

    void setLowThreshold(float lowThreshold);
    void setHighThreshold(float highThreshold);

signals:
    void pushEdgeImage(Mat&);

public slots:
    void onPushRawFrame(Mat&);
};

#endif // CANNYFILTER_H
