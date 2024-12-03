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
        id: cameraWarningButton
        text: "Camera"
        onClicked: cameraWarningDialog.open()
        anchors.centerIn: parent
    }

    CameraWarning{
        id: cameraWarningDialog
    }
}
