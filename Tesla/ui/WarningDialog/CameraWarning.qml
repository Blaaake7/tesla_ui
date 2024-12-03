import QtQuick 2.0
import QtQuick.Window 2.13
import QtQuick.Controls 2.12
import QtQuick.Layouts 1.13

Dialog {
    id: cameraWarningDialog
    title: "cameraWarning"
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
        Image {
            id: opencvImage
            anchors.fill: parent
            fillMode: Image.PreserveAspectFit
            property bool counter: false
            visible: false
            source: "image://live/image"
            asynchronous: false
            cache: false

            function reload() {
                counter = !counter
                source = "image://live/image?id=" + counter
            }
        }

        TextField {
            id: videoPath
            placeholderText: "Video Path or Video Index"
            cursorVisible: true
            width: startButton.width * 3
            text: ""  // Reset text
        }

        Button {
            id: startButton
            text: "Open"
            onClicked: {
                if (videoPath.text !== "") {
                    videoStreamer.openVideoCamera(videoPath.text)
                    opencvImage.visible = true
                } else {
                    console.log("Please enter a valid video path or index.")
                }
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
}
