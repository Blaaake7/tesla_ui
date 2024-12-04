import QtQuick 2.0
import QtLocation 5.15
import QtPositioning 5.15
import QtQuick.Controls 2.12

Rectangle{
    id: rightScreen

    anchors.top: parent.top
    anchors.bottom: bottomBar.top
    anchors.right: parent.right
    width: parent.width * 2/3

    Image {
        id: mapImage
        anchors.fill: parent
        source: "qrc:/ui/assets/mapImage.png"
    }

//    Map {
//      id: map
//      anchors.fill: parent
//      plugin: mapPlugin
//      center: QtPositioning.coordinate(59.90, 10.75)

//    }

//    Plugin {
//      id: mapPlugin
//      name: "osm"
//      PluginParameter {
//        name: "osm.mapping.custom.host";
//        value: "https://tile.thunderforest.com/cycle/%z/%x/%y.png?apikey=4b9292a9ffb742db9e1db748034844c5"
//      }
//    }

    Image {
        id: lockIcon
        anchors.left: parent.left
        anchors.top: parent.top
        anchors.margins: 20
        width: parent.width / 40
        fillMode: Image.PreserveAspectFit
        source: systemHandler.carLocked ? "qrc:/ui/assets/padlock.png" : "qrc:/ui/assets/padlock-unlock.png"
        MouseArea {
            anchors.fill: parent
            onClicked: systemHandler.setCarLocked(!systemHandler.carLocked)
        }
    }

    Text {
        id: dateTimeDisplay
        anchors.left: lockIcon.right
        anchors.leftMargin: 40
        anchors.bottom: lockIcon.bottom
        font.pixelSize: 13
        font.bold: true
        color: "black"
        text: systemHandler.currentTime
    }

    Text {
        id: outdoorTemperatureDisplay
        anchors.left: dateTimeDisplay.right
        anchors.leftMargin: 40
        anchors.bottom: lockIcon.bottom
        font.pixelSize: 13
        font.bold: true
        color: "black"
        text: dataProvider.zone1Temperature + " °C"
    }

    Text {
        id: userNameDisplay
        anchors.left: outdoorTemperatureDisplay.right
        anchors.leftMargin: 40
        anchors.bottom: lockIcon.bottom
        font.pixelSize: 13
        font.bold: true
        color: "black"
        text: systemHandler.userName
    }

    NavigationSearchBox {
        id: navSearchBox

        width: parent.width * 1/3
        height: parent.height * 1/12
        anchors.left: lockIcon.left
        anchors.top: lockIcon.bottom
        anchors.topMargin: 15
    }
}
