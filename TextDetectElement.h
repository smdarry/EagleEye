#ifndef TEXTDETECTELEMENT_H
#define TEXTDETECTELEMENT_H

#include "BaseElement.h"
#include "VideoSource.h"

class TextDetectElement : public BaseElement<Mat>, public PushVideoListener
{
public:
    TextDetectElement();

    virtual void onPush(Mat& frame);
};

#endif // TEXTDETECTELEMENT_H
