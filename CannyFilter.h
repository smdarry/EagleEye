#ifndef CANNYFILTER_H
#define CANNYFILTER_H

#include "VideoSource.h"

class CannyFilter : public BaseElement<Mat>, public PushVideoListener
{
private:
    float _lowThreshold;
    float _highThreshold;

public:
    CannyFilter();

    void setLowThreshold(float lowThreshold);
    void setHighThreshold(float highThreshold);

    virtual void onPush(Mat& frame);
};

#endif // CANNYFILTER_H
