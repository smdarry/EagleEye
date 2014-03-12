#ifndef TEXTDETECTELEMENT_H
#define TEXTDETECTELEMENT_H

#include <QObject>

#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>

using namespace cv;

class TextDetectElement : public QObject
{
    Q_OBJECT
public:
    TextDetectElement();

signals:
    void pushResultImage(Mat& image);

public slots:
    void onPushRawFrame(Mat& frame);
    void onPushEdgeImage(Mat& frame);
};

#endif // TEXTDETECTELEMENT_H
