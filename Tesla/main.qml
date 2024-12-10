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

    WarningDialog {
        id: warningDialog
    }

    LeftCameraWarning {
        id: leftCameraWarning
    }

    RightCameraWarning {
        id: rightCameraWarning
    }

    Timer {
        id: leftCameraTimer
        interval: 5000 // 5초
        repeat: false
        onTriggered: {
            leftCameraWarning.close();
            checkConditionsTimer.isLeftCameraDialogVisible = false;
            checkConditionsTimer.isLeftCameraTimerRunning = false;
        }
    }

    Timer {
        id: checkConditionsTimer
        interval: 1000 // 1초 간격으로 조건 확인
        repeat: true
        running: true
        property bool isLeftCameraDialogVisible: false
        property bool isLeftCameraTimerRunning: false

        onTriggered: {
            let zone1Condition = dataProvider.doorStatus === 1 && dataProvider.zone1Distance <= 20;

            // Zone1 조건 확인 (Left Camera Warning)
            if (zone1Condition && !isLeftCameraDialogVisible && !isLeftCameraTimerRunning) {
                isLeftCameraDialogVisible = true;
                isLeftCameraTimerRunning = true;
                leftCameraWarning.open();

                // 5초 후 LeftCameraWarning 닫기 (Timer 시작)
                leftCameraTimer.start();
            }
        }
    }


//    Column {
//        anchors.left: parent.left
//        anchors.top: parent.top
//        anchors.margins: 15
//        spacing: 10

//        Text {
//            text: "Zone 1 Distance: " + dataProvider.zone1Distance.toFixed(2) + " cm"
//            font.pointSize: 11
//        }

//        Text {
//            text: "Zone 1 Temperature: " + dataProvider.zone1Temperature + " °C"
//            font.pointSize: 11
//        }

//        Text {
//            text: "Zone 2 CO2 Level: " + dataProvider.zone2CO2 + " ppm"
//            font.pointSize: 11
//        }

//        Text {
//            text: "Zone 3 Distance: " + dataProvider.zone3Distance.toFixed(2) + " cm"
//            font.pointSize: 11
//        }
//    }
}
