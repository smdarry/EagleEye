
#ifndef QOPENCVWIDGET_H
#define QOPENCVWIDGET_H

#include <QPixmap>
#include <QLabel>
#include <QWidget>
#include <QVBoxLayout>
#include <QImage>

#include <opencv2/core/core.hpp>

using namespace cv;

class QOpenCVWidget : public QWidget {
    private:
        QLabel *imagelabel;
        QVBoxLayout *layout;
        
        QImage image;
        
    public:
        QOpenCVWidget(QWidget *parent = 0);
        ~QOpenCVWidget(void);
        void putImage(Mat&);

        QImage mat2QImage(const Mat3b &src);
        QImage mat2QImage(const Mat1b &src);
        QImage mat2QImage(const Mat_<double> &src);
        Mat correctGamma(Mat& img, double gamma);
}; 

#endif
