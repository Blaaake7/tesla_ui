#include "camerareceiveimage.h"
#include <QDebug>
#include <QBuffer>

#define WIDTH 640 //수신 영상 widht
#define HEIGHT 480 // 수신 영상 height
#define FRAME_SIZE (WIDTH * HEIGHT * 2) // 프레임 하나의 크기
#define PORT 12346 // 서버 포트 번호

// 서버 초기화 후 클라이언트 연결 대기
CameraReceiver::CameraReceiver(QObject *parent) : QObject(parent), m_socket(nullptr)
{
    if (!m_server.listen(QHostAddress::Any, PORT)) {
        qDebug() << "Server failed to start on port" << PORT;
        return;
    }
    qDebug() << "Server started. Waiting for connection...";

    connect(&m_server, &QTcpServer::newConnection, this, &CameraReceiver::onNewConnection);
}

// 클라이언트가 연결되면 QTcpSocket을 설정하고 관련 신호에 대한 연결을 설정
void CameraReceiver::onNewConnection()
{
    m_socket = m_server.nextPendingConnection();
    qDebug() << "Client connected.";

    connect(m_socket, &QTcpSocket::readyRead, this, &CameraReceiver::onReadyRead);
    connect(m_socket, &QTcpSocket::disconnected, this, &CameraReceiver::onDisconnected);
}

// 수신된 데이터를 프레임 버퍼에 추가하고 완전한 프레임을 처리
void CameraReceiver::onReadyRead()
{
    m_frameBuffer.append(m_socket->readAll());

    while (m_frameBuffer.size() >= FRAME_SIZE) {
        QByteArray frameData = m_frameBuffer.left(FRAME_SIZE);
        m_frameBuffer.remove(0, FRAME_SIZE);

        processFrame(frameData);
    }
}

// 소켓을 정리하고 프레임 버퍼를 초기화
void CameraReceiver::onDisconnected()
{
    qDebug() << "Client disconnected.";
    m_socket->deleteLater();
    m_socket = nullptr;
    m_frameBuffer.clear();
}

// 프레임 데이터를 처리하여 QImage로 변환
void CameraReceiver::processFrame(const QByteArray& frameData)
{
    QImage image(WIDTH, HEIGHT, QImage::Format_RGB888);
    int index = 0;

    for (int i = 0; i < HEIGHT; ++i) {
        for (int j = 0; j < WIDTH; j += 2) {
            int y0 = static_cast<unsigned char>(frameData[index]);
            int u  = static_cast<unsigned char>(frameData[index + 1]);
            int y1 = static_cast<unsigned char>(frameData[index + 2]);
            int v  = static_cast<unsigned char>(frameData[index + 3]);

            index += 4;

            auto clip = [](int x) { return std::min(255, std::max(0, x)); };

            int r0 = clip(y0 + 1.402 * (v - 128));
            int g0 = clip(y0 - 0.344136 * (u - 128) - 0.714136 * (v - 128));
            int b0 = clip(y0 + 1.772 * (u - 128));

            int r1 = clip(y1 + 1.402 * (v - 128));
            int g1 = clip(y1 - 0.344136 * (u - 128) - 0.714136 * (v - 128));
            int b1 = clip(y1 + 1.772 * (u - 128));

            image.setPixelColor(j, i, QColor(r0, g0, b0));
            image.setPixelColor(j + 1, i, QColor(r1, g1, b1));
        }
    }

    m_imageUrl = imageToUrl(image);
    emit imageUrlChanged();
}

// 이미지를 URL로 바꿈
QUrl CameraReceiver::imageToUrl(const QImage& image)
{
    QByteArray byteArray;
    QBuffer buffer(&byteArray);
    buffer.open(QIODevice::WriteOnly);
    image.save(&buffer, "png");
    QString base64 = QString::fromUtf8(byteArray.toBase64());
    return QUrl(QString("data:image/png;base64,") + base64);
}
