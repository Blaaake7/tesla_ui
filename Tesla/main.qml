import QtQuick 2.13
import QtQuick.Window 2.13
import QtQuick.Controls 2.13
import QtQuick.Layouts 1.13
import "ui/BottomBar"
import "ui/RightScreen"
import "ui/LeftScreen"
import "ui/WarningDialog"

Window {
    id: mainWindow
    width: 1280
    height: 720
    visible: true
    title: qsTr("Tesla Info")

    LeftScreen {
        id: leftScreen
    }

    RightScreen {
        id: rightScreen
    }

    BottomBar {
        id: bottomBar
    }

    Button {
        id: warningButton
        text: "Warning Button"
        onClicked: warningDialog.open()
        anchors.centerIn: parent
    }

    WarningDialog {
        id: warningDialog
    }

    Button {
        text: "Received Image"
        onClicked: cameraPopup.open()
    }

    Popup {
        id: cameraPopup
        width: 640
        height: 480
        modal: true
        focus: true
        closePolicy: Popup.CloseOnEscape | Popup.CloseOnPressOutside

        Image {
            anchors.fill: parent
            source: cameraReceiver.imageUrl
            fillMode: Image.PreserveAspectFit
            onStatusChanged: console.log("Image Url:", cameraReceiver.imageUrl)
        }
    }

}
