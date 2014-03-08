#-------------------------------------------------
#
# Project created by QtCreator 2014-03-07T17:02:14
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = EagleEye
TEMPLATE = app


SOURCES += main.cpp\
        QOpenCVWidget.cpp \
    Buffer.cpp \
    CameraWindow.cpp \
    VideoSource.cpp \
    TextDetectElement.cpp \
    CannyFilter.cpp

HEADERS  +=\
            QOpenCVWidget.h \
    BaseElement.h \
    Buffer.h \
    VideoSource.h \
    CameraWindow.h \
    TextDetectElement.h \
    CannyFilter.h

INCLUDEPATH += C:\\opencv2.4.8\\Release\\install\\include

LIBS += -LC:\\opencv2.4.8\\Release\\lib \
    -lopencv_core248.dll\
    -lopencv_features2d248.dll\
    -lopencv_flann248.dll\
    -lopencv_highgui248.dll\
    -lopencv_imgproc248.dll\
    -lopencv_ml248.dll\
    -lopencv_calib3d248.dll
