import QtQuick 2.0

Rectangle {
    id: leftScreen
    anchors.left: parent.left
    anchors.right: rightScreen.left
    anchors.bottom: bottomBar.top
    anchors.top: parent.top
    color: "#f4f6f8"

    Image {
        id: carRender
        anchors.centerIn: parent
        width: parent.width * .95
        fillMode: Image.PreserveAspectFit
        source: "qrc:/ui/assets/teslaInfoImage.png"
    }

    Item {
        id: batteryIndicator
        anchors.top: parent.top
        anchors.right: parent.right
        anchors.margins: 20
        width: batteryImage.width + batteryText.width + 10
        height: Math.max(batteryImage.height, batteryText.height)

        Text {
            id: batteryText
            anchors.right: batteryImage.left
            anchors.rightMargin: 5
            anchors.verticalCenter: parent.verticalCenter
            font.pixelSize: 14
            color: "black"
            text: "98%"
        }

        Image {
            id: batteryImage
            anchors.right: parent.right
            anchors.verticalCenter: parent.verticalCenter
            source: "qrc:/ui/assets/full-battery.png"
            width: 30
            height: 20
        }
    }
}
