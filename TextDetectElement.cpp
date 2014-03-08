#include "TextDetectElement.h"

#include <QDebug>
#include <QLine>
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

    QLinkedList<QLine> listOfRays;
    float alpha = 0.5;

    // Traverse the whole image
    for (int y = 0; y < frame.rows; ++y) {
        for (int x = 0; x < frame.cols; ++x) {

            QPoint p(x, y);
            uchar p_i = frame.at<uchar>(y, x);

            // No need to follow a black pixel
            if(p_i == 0)
                continue;

            // Compute and normalize gradient at (y, x)
            short g_p_x = grad_x.at<short>(y, x);
            short g_p_y = grad_y.at<short>(y, x);

            QVector2D grad_p(g_p_x, g_p_y);
            grad_p.normalize();

            uchar new_p_i = 0;
            int new_x = x;
            int new_y = y;

            // Follow gradient until we meet another pixel with intensity > 0
            bool isOutOfBounds = false;
            do
            {
                // Move in the direction of the gradient according to p = p + alpha * g_x
                new_x = (int)floor(new_x + grad_p.x() * alpha);
                new_y = (int)floor(new_y + grad_p.y() * alpha);

                // Check if we go beyond image's bounds
                if(new_x >= frame.cols || new_y >= frame.rows)
                    isOutOfBounds = true;
                if(new_x < 0 || new_y < 0)
                    isOutOfBounds = true;

                // Get pixel intensity at new position
                new_p_i = frame.at<uchar>(new_y, new_x);

            } while(new_p_i == 0 && !isOutOfBounds);

            if(isOutOfBounds)
                continue;

            // When we get here we found pixel q, compute its gradient
            QPoint q(new_x, new_y);
            short g_q_x = grad_x.at<short>(new_y, new_x);
            short g_q_y = grad_y.at<short>(new_y, new_x);

            QVector2D grad_q(g_q_x, g_q_y);
            grad_q.normalize();

            // Compare (dot product) gradient of pixel p and q and see if they
            // point in roughly opposite directions
            float dotProduct = QVector2D::dotProduct(grad_p, grad_q);
            if(dotProduct < 0)
            {
                QLine ray(p, q);
                listOfRays.append(ray);
                //qDebug() << "DOT product between q and p:" << dotProduct;
            }
        }
    }

    // Draw the rays found
    QLinkedList<QLine>::Iterator it;
    for(it = listOfRays.begin(); it != listOfRays.end(); ++it)
    {
        QLine line = (*it);
        cv::Point p1(line.x1(), line.y1());
        cv::Point p2(line.x2(), line.y2());

        cv::line(frame, p1, p2, CV_RGB(0, 255, 0), 1, 8, 0);
    }

    notify(frame);
}
