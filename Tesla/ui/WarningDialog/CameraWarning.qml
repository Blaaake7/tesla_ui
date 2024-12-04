import QtQuick 2.0
import QtQuick.Window 2.13
import QtQuick.Controls 2.12
import QtQuick.Layouts 1.13

Dialog {
    id: cameraWarningDialog
    title: "Camera Warning"
    x: (parent.width - width) / 2
    y: (parent.height - height) / 2
    width: 800
    height: 600
    modal: true
    focus: true
    closePolicy: Popup.CloseOnEscape | Popup.CloseOnPressOutside

    background: Rectangle {
        id: dialogBackground
        color: "white"
        radius: 5
    }

    ColumnLayout {
        anchors.fill: parent
        anchors.margins: 10

        Image {
            id: opencvImage
            anchors.fill: parent
            fillMode: Image.PreserveAspectFit
            visible: false
            source: "image://live/image"
            asynchronous: false
            cache: false

            function reload() {
                source = "image://live/image?id=" + Math.random();
            }
        }

        Button {
            text: "OK"
            Layout.alignment: Qt.AlignHCenter
            onClicked: cameraWarningDialog.close()
        }

        // Handling image updates
        Connections {
            target: liveImageProvider
            onImageChanged: {
                opencvImage.reload()
            }
        }
    }

    onOpened: {
        // 팝업이 열릴 때 카메라 연결
        console.log("Opening camera connection...");
        videoStreamer.openVideoCamera("/dev/video1");
        opencvImage.visible = true;
    }
}
