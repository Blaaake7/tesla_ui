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

    Timer {
        id: checkConditionsTimer
        interval: 1000 // 1초 간격으로 조건 확인
        repeat: true
        running: true
        property bool isCameraDialogVisible: false

        onTriggered: {
            // Camera Warning 조건 확인
            if (dataProvider.doorStatus === 1 && dataProvider.zone1Distance <= 30) {
                if (!isCameraDialogVisible) {
                    isCameraDialogVisible = true;
                    cameraWarningDialog.open();

                    // 2초 후 CameraWarning 닫기
                    Qt.callLater(function() {
                        cameraWarningDialog.close();
                        isCameraDialogVisible = false;
                    }, 5000);
                }
            }
            // Sleeping Driving Warning 조건 확인 (Camera Warning 조건과 충돌하지 않을 경우)
            else if (dataProvider.sleepScore >= 90 && !isCameraDialogVisible) {
                warningDialog.showDialog();
            }
        }
    }

    CameraWarning{
        id: cameraWarningDialog
    }

    Column {
        anchors.left: parent.left
        anchors.top: parent.top
        anchors.margins: 15
        spacing: 10

        Text {
            text: "Zone 1 Distance: " + dataProvider.zone1Distance.toFixed(2) + " cm"
            font.pointSize: 11
        }

        Text {
            text: "Zone 1 Temperature: " + dataProvider.zone1Temperature + " °C"
            font.pointSize: 11
        }

        Text {
            text: "Zone 2 CO2 Level: " + dataProvider.zone2CO2 + " ppm"
            font.pointSize: 11
        }
    }
}
