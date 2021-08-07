import QtQuick 2.0

Image {

    id: leftButton
    source: "qrc:images/arrow_left.png"
    anchors.margins: 20

    signal clicked()

    MouseArea {
        id: goLeftMouseArea
        anchors.fill: parent
        onClicked: clicked()
    }
}




