import QtQuick 2.13
import QtQuick.Layouts 1.13

Rectangle {
    id: bottomBar
    anchors.left: parent.left
    anchors.right: parent.right
    anchors.bottom: parent.bottom
    color: "black"
    height: parent.height / 12

    Image {
        id: carSettingIcon
        anchors.left: parent.left
        anchors.leftMargin: 30
        anchors.verticalCenter: parent.verticalCenter
        height: parent.height * .85
        fillMode: Image.PreserveAspectFit
        source: "qrc:/ui/assets/car.png"
    }

    RowLayout {
        width: parent.width * 0.3
        height: parent.height
        anchors.centerIn: parent
        anchors.horizontalCenter: parent.horizontalCenter
        spacing: 10

        Repeater {
            model: ["call", "gear", "voice", "spotify", "bluetooth"]
            delegate: Image {
                Layout.preferredWidth: 35
                Layout.preferredHeight: 35
                Layout.alignment: Qt.AlignVCenter
                source: "qrc:/ui/assets/" + modelData + ".png"
                fillMode: Image.PreserveAspectFit

                scale: iconMouseArea.containsMouse ? 1.2 : 1.0

                Behavior on scale {
                    NumberAnimation { duration: 30 }
                }

                MouseArea {
                    id: iconMouseArea
                    anchors.fill: parent
                    hoverEnabled: true
                }
            }
        }
    }
}
