
#include "QOpenCVWidget.h"

// Constructor
QOpenCVWidget::QOpenCVWidget(QWidget *parent) : QWidget(parent) {
    layout = new QVBoxLayout;
    imagelabel = new QLabel;
    QImage dummy(100,100,QImage::Format_RGB32);
    image = dummy;
    layout->addWidget(imagelabel);
    for (int x = 0; x < 100; x ++) {
        for (int y =0; y < 100; y++) {
            image.setPixel(x,y,qRgb(x, y, y));
        }
    }
    imagelabel->setPixmap(QPixmap::fromImage(image));

    setLayout(layout);
}

QOpenCVWidget::~QOpenCVWidget(void) {
    
}

void QOpenCVWidget::putImage(Mat& cvimage) {
    //cvimage = correctGamma(cvimage, 2.2);

    if(cvimage.channels() == 3) {
        imagelabel->setPixmap(QPixmap::fromImage(mat2QImage((Mat3b)cvimage)));
    }
    else if(cvimage.channels() == 1) {
        imagelabel->setPixmap(QPixmap::fromImage(mat2QImage((Mat1b)cvimage)));
    }
}

QImage QOpenCVWidget::mat2QImage(const Mat3b &src) {
    QImage dest(src.cols, src.rows, QImage::Format_ARGB32);
    for (int y = 0; y < src.rows; ++y) {
        QRgb *destrow = (QRgb*)dest.scanLine(y);
        for (int x = 0; x < src.cols; ++x) {
            Vec3b intensity = src.at<Vec3b>(y, x);
            destrow[x] = qRgba(intensity.val[2], intensity.val[1], intensity.val[0], 255);
        }
    }
    return dest;
}

QImage QOpenCVWidget::mat2QImage(const Mat1b &src) {
    QImage dest(src.cols, src.rows, QImage::Format_ARGB32);
    for (int y = 0; y < src.rows; ++y) {
        QRgb *destrow = (QRgb*)dest.scanLine(y);
        for (int x = 0; x < src.cols; ++x) {
            uchar intensity = src.at<uchar>(y, x);
            destrow[x] = qRgba(intensity, intensity, intensity, 255);
        }
    }
    return dest;
}

QImage QOpenCVWidget::mat2QImage(const Mat_<double> &src)
{
    double scale = 255.0;
    QImage dest(src.cols, src.rows, QImage::Format_ARGB32);
    for (int y = 0; y < src.rows; ++y) {
        const double *srcrow = src[y];
        QRgb *destrow = (QRgb*)dest.scanLine(y);
        for (int x = 0; x < src.cols; ++x) {
            unsigned int color = srcrow[x] * scale;
            destrow[x] = qRgba(color, color, color, 255);
        }
    }
    return dest;
}

Mat QOpenCVWidget::correctGamma(Mat& img, double gamma) {
    double inverse_gamma = 1.0 / gamma;

    Mat lut_matrix(1, 256, CV_8UC1 );
    uchar * ptr = lut_matrix.ptr();
    for( int i = 0; i < 256; i++ ) {
        ptr[i] = (int)( pow( (double) i / 255.0, inverse_gamma ) * 255.0 );
    }

    Mat result;
    LUT(img, lut_matrix, result);

    return result;
}
