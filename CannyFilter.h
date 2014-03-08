#ifndef CANNYFILTER_H
#define CANNYFILTER_H

#include "VideoSource.h"

class CannyFilter : public BaseElement<Mat>, public PushVideoListener
{
public:
    CannyFilter();

    virtual void onPush(Mat& frame);
};

#endif // CANNYFILTER_H
