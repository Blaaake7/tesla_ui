import QtQuick 2.13
import QtQuick.Window 2.13
import QtQuick.Controls 2.13
import QtQuick.Layouts 1.13
import "ui/BottomBar"
import "ui/RightScreen"
import "ui/LeftScreen"
import "ui/WarningDialog"

// 메인 윈도우 설정
Window {
    id: mainWindow
    width: 1280                // 창의 너비
    height: 720                // 창의 높이
    visible: true              // 창을 보이게 함
    title: qsTr("Tesla Info")  // 창 제목 설정

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

    // 왼쪽 카메라 경고를 제어하는 타이머
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

    // 조건을 체크하는 타이머
    Timer {
        id: checkConditionsTimer
        interval: 1000 // 1초 간격으로 조건 확인
        repeat: true
        running: true
        property bool isLeftCameraDialogVisible: false
        property bool isLeftCameraTimerRunning: false
        property bool isSleepingDialogVisible: false

        onTriggered: {
            // Zone1 조건 : 문이 열려 있고 거리 <= 20cm인 경우
            let zone1Condition = dataProvider.doorStatus === 1 && dataProvider.zone1Distance <= 20;
            let sleepingCondition = dataProvider.sleepScore >= 510;

            // Zone1 조건 확인 (Left Camera Warning)
            if (zone1Condition && !isLeftCameraDialogVisible && !isLeftCameraTimerRunning) {
                isLeftCameraDialogVisible = true;
                isLeftCameraTimerRunning = true;
                leftCameraWarning.open();

                // 5초 후 LeftCameraWarning 닫기 (Timer 시작)
                leftCameraTimer.start();
            }

            // 수면 조건 확인 및 경고 다이얼로그 표시
            if (sleepingCondition && !isSleepingDialogVisible) {
                isSleepingDialogVisible = true;
                warningDialog.showDialog();

                // Dialog 닫힌 후 상태 초기화
                warningDialog.closed.connect(() => {
                    isSleepingDialogVisible = false;
                });
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
