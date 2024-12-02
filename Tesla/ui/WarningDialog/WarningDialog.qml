import QtQuick 2.13
import QtQuick.Window 2.13
import QtQuick.Controls 2.13
import QtQuick.Layouts 1.13

Dialog {
    id: warningDialog
    title: "Warning"
    x: (parent.width - width) / 2
    y: (parent.height - height) / 2
    width: 450
    height: 300
    modal: true
    focus: true
    closePolicy: Popup.CloseOnEscape | Popup.CloseOnPressOutside

    background: Rectangle {
        id: dialogBackground
        color: "red"
        radius: 5
    }

    ColumnLayout {
        anchors.fill: parent
        anchors.margins: 10

        Label {
            text: "*Sleeping driving detected*\n\nSleeping driving can take away everything."
            color: "white"
            font.pixelSize: 18
            Layout.fillWidth: true
            horizontalAlignment: Text.AlignHCenter
            wrapMode: Text.WordWrap
        }

        Button {
            text: "OK"
            Layout.alignment: Qt.AlignHCenter
            onClicked: warningDialog.close()
        }
    }

    PropertyAnimation {
        id: colorAnimation
        target: dialogBackground
        property: "color"
        from: "red"
        to: "orange"
        duration: 300
        running: false
    }

    Timer {
        id: blinkTimer
        interval: 300
        repeat: true
        running: false
        property int count: 0
        onTriggered: {
            if (count % 2 == 0) {
                colorAnimation.from = "red"
                colorAnimation.to = "orange"
            } else {
                colorAnimation.from = "orange"
                colorAnimation.to = "red"
            }
            colorAnimation.start()
            count++
            if (count >= 21) {  // Blink 10 times
                stop()
                dialogBackground.color = "red"
            }
        }
    }

    onOpened: {
        blinkTimer.count = 0
        blinkTimer.start()
    }
}
