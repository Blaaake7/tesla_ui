#ifndef CAMERARECEIVER_H
#define CAMERARECEIVER_H

#include <QObject>
#include <QTcpServer>
#include <QTcpSocket>
#include <QImage>
#include <QUrl>

class CameraReceiver : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QUrl imageUrl READ imageUrl NOTIFY imageUrlChanged)

public:
    explicit CameraReceiver(QObject *parent = nullptr);
    QUrl imageUrl() const { return m_imageUrl; }

signals:
    void imageUrlChanged();

private slots:
    void onNewConnection();
    void onReadyRead();
    void onDisconnected();

private:
    QTcpServer m_server;
    QTcpSocket* m_socket;
    QByteArray m_frameBuffer;
    QImage m_image;
    QUrl m_imageUrl;

    void processFrame(const QByteArray& frameData);
    QUrl imageToUrl(const QImage& image);
};

#endif // CAMERARECEIVER_H
