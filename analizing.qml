import QtQuick 2.0

Rectangle{
    id: rec;
    width: 100;
    height: 200;
    //color: "#66af7979";
    color: "white"

    //radius: 5
    //border.color: "black"
    //border.width: 1
    AnimatedImage{
        id: loadImage
        source: "qrc:/images/cargando.gif";
        anchors.centerIn: parent;
        //anchors.fill: parent;
        /*NumberAnimation on rotation{
            from: 0;
            to: 360;
            duration: 3600;
            loops: Animation.Infinite
        }*/
    }
    Text {
        id: text2

        x: 45;
        y: 150;

        //x: 152
        //y: 139
        color: "black"
        text: qsTr("calculando")
        style: Text.Raised
        font.bold: false
        font.family: "Verdana"
        font.pixelSize: 11

        SequentialAnimation on text{
            PropertyAnimation { to: "calculando."; duration: 1000}
            PropertyAnimation { to: "calculando.."; duration: 1000}
            PropertyAnimation { to: "calculando..."; duration: 1000}
            PropertyAnimation { to: "calculando.."; duration: 1000}
            PropertyAnimation { to: "calculando."; duration: 1000}
            PropertyAnimation { to: "calculando"; duration: 1000}
            loops: Animation.Infinite;
        }

    }

}
