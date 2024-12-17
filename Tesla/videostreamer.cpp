#include "videostreamer.h"
#include <QDebug>

// 생성자: QTimer를 설정하고 초기화
// 카메라 스트리밍을 위한 타이머를 준비하고, 타이머의 timeout 시그널에 스트리밍 함수 연결
VideoStreamer::VideoStreamer(QObject *parent)
    : QObject(parent), cap(), tUpdate(this)
{
    connect(&tUpdate, &QTimer::timeout, this, &VideoStreamer::streamVideo);
}

// 소멸자: 카메라 장치를 해제하고 타이머를 중지
VideoStreamer::~VideoStreamer()
{
    if (cap.isOpened())
        cap.release();
    tUpdate.stop();
}

// 주기적으로 호출되어 카메라에서 프레임을 캡처하고 이미지를 QImage로 변환
void VideoStreamer::streamVideo()
{
    if (cap.isOpened())
    {
        cap >> frame; // 프레임 캡처
        if (!frame.empty())
        {
            QImage img(frame.data, frame.cols, frame.rows, frame.step, QImage::Format_RGB888);
            img = img.rgbSwapped(); // RGB 순서 맞춤
            emit newImage(img); // 새로운 이미지 신호 전송
        }
        else
        {
            qWarning() << "Frame is empty.";
        }
    }
    else
    {
        qWarning() << "Camera is not opened.";
    }
}

// 왼쪽 카메라 장치 (/dev/video1) 열기
void VideoStreamer::openLeftCamera()
{
    openCamera("/dev/video1"); // 왼쪽 카메라 장치 경로
}

// 오른쪽 카메라 장치 (/dev/video3) 열기
void VideoStreamer::openRightCamera()
{
    openCamera("/dev/video3"); // 오른쪽 카메라 장치 경로
}

// 카메라, 비디오 경로 열기
void VideoStreamer::openVideoCamera(QString path)
{
    if (cap.isOpened())
    {
        cap.release(); // 기존에 열려 있던 장치 닫기
    }

    if (path.length() == 1)
    {
        cap.open(path.toInt()); // 장치 번호로 카메라 열기
    }
    else
    {
        cap.open(path.toStdString()); // 경로로 카메라 열기
    }
    
    // 카메라 성공적으로 열림
    if (cap.isOpened())
    {
        qDebug() << "Camera opened successfully.";

        // FPS 가져오기
        double fps = cap.get(cv::CAP_PROP_FPS);
        if (fps <= 0)
        {
            fps = 30.0; // 기본 FPS 설정
        }

        qDebug() << "Camera FPS:" << fps;

        // 타이머 시작
        tUpdate.start(1000 / fps); // FPS에 따라 타이머 설정
    }
    else
    {
        qWarning() << "Failed to open camera.";
    }
}

// 카메라 장치를 닫고, 타이머 중지
void VideoStreamer::closeCamera()
{
    if (cap.isOpened())
    {
        cap.release(); // 카메라 장치 해제
    }
    tUpdate.stop(); // 타이머 중지
}

//카메라 장치를 열고, 타이머 시작
void VideoStreamer::openCamera(const QString &devicePath)
{
    if (cap.isOpened())
    {
        cap.release();
    }

    cap.open(devicePath.toStdString(), cv::CAP_V4L2);

    if (cap.isOpened())
    {
        qDebug() << "Camera opened successfully at" << devicePath;

        double fps = cap.get(cv::CAP_PROP_FPS);
        if (fps <= 0)
        {
            fps = 30.0;
        }

        tUpdate.start(1000 / fps);
    }
    else
    {
        qWarning() << "Failed to open camera device:" << devicePath;
    }
}

