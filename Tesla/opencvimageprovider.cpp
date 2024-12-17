#include "opencvimageprovider.h"

// 초기 이미지를 검정색으로 설정
OpencvImageProvider::OpencvImageProvider(QObject *parent) : QObject(parent), QQuickImageProvider(QQuickImageProvider::Image)
{
    image = QImage(200,200,QImage::Format_RGB32);
    image.fill(QColor("black"));
}

// QML에서 이 함수가 호출되면 현재 이미지를 반환하고, 이미지 크기를 조정
QImage OpencvImageProvider::requestImage(const QString &id, QSize *size, const QSize &requestedSize)
{
    Q_UNUSED(id);

    if(size){
        *size = image.size();
    }

    if(requestedSize.width() > 0 && requestedSize.height() > 0) {
        image = image.scaled(requestedSize.width(), requestedSize.height(), Qt::KeepAspectRatio);
    }
    return image;
}

// 새로운 이미지가 유효하고 기존 이미지와 다를 경우, 이미지를 갱신하고 `imageChanged` signal를 발생
void OpencvImageProvider::updateImage(const QImage &image)
{
    if(!image.isNull() && this->image != image) {
        this->image = image;
        emit imageChanged();
    }
}
