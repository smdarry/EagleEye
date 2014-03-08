#include "CannyFilter.h"

#include "opencv2/core/core.hpp"
#include "opencv2/imgproc/imgproc.hpp"

CannyFilter::CannyFilter()
{
}

void CannyFilter::onPush(Mat &frame)
{
    // Convert to grayscale
    Mat grayImage;
    cvtColor(frame, grayImage, CV_RGB2GRAY);

    // Create Canny Image
    double threshold_low = 50;
    double threshold_high = 50;
    Mat edgeImage;
    Canny(grayImage, edgeImage, threshold_low, threshold_high, 3);

    notify(edgeImage);
}
