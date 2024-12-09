import QtQuick 2.0
import QtQuick.Window 2.13
import QtQuick.Controls 2.12
import QtQuick.Layouts 1.13

Dialog {
    id: rightCameraDialog
    width: 800
    height: 600
    visible: false
    modal: true
    title: qsTr("Right Camera View")

    ColumnLayout {
        anchors.fill: parent
        spacing: 10

        Rectangle {
            Layout.fillWidth: true
            Layout.fillHeight: true
            color: "black"

            Image {
                id: rightImage
                source: "image://rightLive/"
                fillMode: Image.PreserveAspectFit
                property bool counter: false
                visible: false
                anchors.fill: parent
                asynchronous: false
                cache: false

                function reload() {
                    counter = !counter
                    source = "image://rightLive/?id=" + Math.random()
                }
            }
        }

        Button {
            text: "Close"
            Layout.alignment: Qt.AlignHCenter
            onClicked: {
                rightVideoStreamer.closeCamera(); // 카메라 닫기
                rightCameraDialog.visible = false; // 다이얼로그 닫기
            }
        }
        Connections{
            target: rightImageProvider
            onImageChanged: {
                rightImage.reload()
            }
        }
    }

    onOpened: {
        // 팝업이 열릴 때 카메라 연결
        console.log("Opening camera connection...");
        rightVideoStreamer.openRightCamera();
        rightImage.visible = true;
    }
}
