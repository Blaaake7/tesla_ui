#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include <Controllers/system.h>
#include <Controllers/dataprovider.h>
#include <Controllers/camerareceiveimage.h>
#include <opencvimageprovider.h>
#include <videostreamer.h>

int main(int argc, char *argv[])
{
    #if QT_VERSION < QT_VERSION_CHECK(6, 0, 0)
        QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
    #endif
    QGuiApplication app(argc, argv);

    // 시스템 관련 객체
    System m_systemHandler;
    DataProvider dataProvider;
    CameraReceiver cameraReceiver;

    // 비디오 스트리밍 관련 객체
    VideoStreamer videoStreamer;
    OpencvImageProvider *liveImageProvider(new OpencvImageProvider);

    // QML 엔진
    QQmlApplicationEngine engine;

    // QML 컨텍스트에 객체들 등록
    QQmlContext *context = engine.rootContext();
    context->setContextProperty("systemHandler", &m_systemHandler);
    context->setContextProperty("dataProvider", &dataProvider);
    context->setContextProperty("cameraReceiver", &cameraReceiver);
    context->setContextProperty("videoStreamer", &videoStreamer);
    context->setContextProperty("liveImageProvider", liveImageProvider);

    // 이미지 제공자 등록
    engine.addImageProvider("live", liveImageProvider);

    // QML 파일 로드
    const QUrl url(QStringLiteral("qrc:/main.qml"));
    engine.load(url);

    // 비디오 스트리밍 및 이미지 업데이트 연결
    QObject::connect(&videoStreamer, &VideoStreamer::newImage, liveImageProvider, &OpencvImageProvider::updateImage);

    // 앱 실행
    return app.exec();
}
