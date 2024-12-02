import QtQuick 2.0

Rectangle {
    id: navSearchBox
    radius: 5
    color: "#cccccc"

    Image {
        id: searchIcon
        anchors.left: parent.left
        anchors.leftMargin: 25
        anchors.verticalCenter: parent.verticalCenter
        source: "qrc:/ui/assets/search.png"
        height: parent.height * .45
        fillMode: Image.PreserveAspectFit
    }

    Text {
        id: navigationPlaceHolderText
        visible: navigationTextInput.text === ""
        color: "#373737"
        text: "Navigate"
        anchors.verticalCenter: parent.verticalCenter
        anchors.left: searchIcon.right
        anchors.leftMargin: 20
    }

    TextInput {
        id: navigationTextInput
        clip: true
        anchors.top: parent.top
        anchors.bottom: parent.bottom
        anchors.right: parent.right
        anchors.left: searchIcon.right
        anchors.leftMargin: 20
        anchors.rightMargin: 20
        verticalAlignment: Text.AlignVCenter
        font.pixelSize: 16
        color: "#373737"
    }
}
