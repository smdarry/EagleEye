#include "TextDetectElement.h"

#include "opencv2/core/core.hpp"
#include "opencv2/imgproc/imgproc.hpp"

TextDetectElement::TextDetectElement()
{
}

void TextDetectElement::onPush(Mat &frame)
{
    int scale = 1;
    int delta = 0;

    GaussianBlur(frame, frame, Size(3,3), 0, 0, BORDER_DEFAULT);

    /// Generate grad_x and grad_y
    Mat grad_x, grad_y;
    Mat abs_grad_x, abs_grad_y;

    /// Gradient X
    //Scharr( src_gray, grad_x, ddepth, 1, 0, scale, delta, BORDER_DEFAULT );
    Sobel(frame, grad_x, CV_16S, 1, 0, 3, scale, delta, BORDER_DEFAULT);
    convertScaleAbs(grad_x, abs_grad_x);

    /// Gradient Y
    //Scharr( src_gray, grad_y, ddepth, 0, 1, scale, delta, BORDER_DEFAULT );
    Sobel(frame, grad_y, CV_16S, 0, 1, 3, scale, delta, BORDER_DEFAULT);
    convertScaleAbs(grad_y, abs_grad_y);

    notify(frame);
}
