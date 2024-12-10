import QtQuick 2.0
import QtQuick.Window 2.13
import QtQuick.Controls 2.12
import QtQuick.Layouts 1.13

Dialog {
    id: leftCameraWarning
    width: 800
    height: 600
    visible: false
    modal: true
    title: qsTr("Left Camera View")

    ColumnLayout {
        anchors.fill: parent
        spacing: 10

        Rectangle {
            Layout.fillWidth: true
            Layout.fillHeight: true
            color: "black"

            Image {
                id: leftImage
                source: "image://leftLive/"
                fillMode: Image.PreserveAspectFit
                property bool counter: false
                visible: false
                anchors.fill: parent
                asynchronous: false
                cache: false

                function reload() {
                    counter = !counter
                    source = "image://leftLive/?id=" + counter;
                }
            }
        }

        Button {
            text: "Close"
            Layout.alignment: Qt.AlignHCenter
            onClicked: {
                leftVideoStreamer.closeCamera();
                leftCameraWarning.visible = false;
            }
        }

        Connections {
            target: leftImageProvider
            onImageChanged: {
                leftImage.reload();
            }
        }
    }

    onOpened: {
        console.log("Opening camera connection...");
        leftVideoStreamer.openLeftCamera();
        leftImage.visible = true;
    }

    // 화면 중앙에 위치하도록 설정
    onVisibleChanged: {
        if (visible) {
            x = (mainWindow.width - width) / 2;
            y = (mainWindow.height - height) / 2;
        } else {
            console.log("Left Camera Warning closed");
            checkConditionsTimer.isLeftCameraDialogVisible = false;
            checkConditionsTimer.isLeftCameraTimerRunning = false;
        }
    }
}
