#ifndef VIDEOSTREAMER_H
#define VIDEOSTREAMER_H

#include <QObject>
#include <QTimer>
#include <opencv2/highgui.hpp>
#include <QImage>
#include <iostream>

class VideoStreamer : public QObject
{
    Q_OBJECT
public:
    explicit VideoStreamer(QObject *parent = nullptr);
    ~VideoStreamer();

    // 스트리밍 처리 메서드
    void streamVideo();

public slots:
    // 각각의 카메라를 여는 메서드
    void openLeftCamera();
    void openRightCamera();
    void openVideoCamera(QString path); // 추가된 메서드 선언
    void closeCamera(); // 카메라를 닫는 메서드

private:
    // 공통적인 카메라 열기 메서드
    void openCamera(const QString &devicePath);

    // 내부 변수들
    cv::Mat frame;
    cv::VideoCapture cap;
    QTimer tUpdate;

signals:
    // 새로운 이미지를 전달하는 시그널
    void newImage(QImage &);
};

#endif // VIDEOSTREAMER_H
