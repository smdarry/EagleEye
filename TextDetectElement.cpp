#include "TextDetectElement.h"

#include <QDebug>
#include <QVector2D>

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
    Mat grad_x, grad_y, grad;
    Mat abs_grad_x, abs_grad_y;

    /// Gradient X
    //Scharr( src_gray, grad_x, ddepth, 1, 0, scale, delta, BORDER_DEFAULT );
    Sobel(frame, grad_x, CV_16S, 1, 0, 3, scale, delta, BORDER_DEFAULT);
    convertScaleAbs(grad_x, abs_grad_x);

    /// Gradient Y
    //Scharr( src_gray, grad_y, ddepth, 0, 1, scale, delta, BORDER_DEFAULT );
    Sobel(frame, grad_y, CV_16S, 0, 1, 3, scale, delta, BORDER_DEFAULT);
    convertScaleAbs(grad_y, abs_grad_y);

    /// Total Gradient (approximate)
    addWeighted(abs_grad_x, 0.5, abs_grad_y, 0.5, 0, grad);

    QLinkedList<QPoint> listOfPoints;
    float alpha = 0.5;

    // Traverse the whole image
    for (int y = 0; y < frame.rows; ++y) {
        for (int x = 0; x < frame.cols; ++x) {

            uchar p_i = frame.at<uchar>(y, x);

            // No need to follow a black pixel
            if(p_i == 0)
                continue;

            // Compute and normalize gradient at (y, x)
            short g_x = grad_x.at<short>(y, x);
            short g_y = grad_y.at<short>(y, x);

            QVector2D grad(g_x, g_y);
            grad.normalize();

            uchar new_p_i = 0;
            int new_x = x;
            int new_y = y;

            // Follow gradient until we meet another pixel with intensity > 0
            do
            {
                // Move in the direction of the gradient according to p = p + alpha * g_x
                new_x = (int)floor(new_x + grad.x() * alpha);
                new_y = (int)floor(new_y + grad.y() * alpha);

                // Check if we go beyond image's bounds
                if(new_x >= frame.cols || new_y >= frame.rows)
                    break;

                // Get pixel intensity at new position
                new_p_i = frame.at<uchar>(new_y, new_x);

            } while(new_p_i == 0);
        }
    }

    notify(frame);
}
