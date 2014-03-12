#include "CannyFilter.h"

#include "opencv2/core/core.hpp"
#include "opencv2/imgproc/imgproc.hpp"

CannyFilter::CannyFilter()
{
}

void CannyFilter::setLowThreshold(float lowThreshold)
{
    _lowThreshold = lowThreshold;
}

void CannyFilter::setHighThreshold(float highThreshold)
{
    _highThreshold = highThreshold;
}

void CannyFilter::onPushRawFrame(Mat &frame)
{
    // Convert to grayscale
    Mat grayImage;
    cvtColor(frame, grayImage, CV_RGB2GRAY);

    // Create Canny Image
    Mat edgeImage;
    Canny(grayImage, edgeImage, _lowThreshold, _highThreshold, 3);

    emit pushEdgeImage(edgeImage);
}
