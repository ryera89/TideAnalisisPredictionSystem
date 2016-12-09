import QtQuick 2.0


Rectangle{
    id: rec;
    anchors.fill: parent
    color: "#b30f0000";
    Image {
        id: loadImage
        source: "images/load.png";
        anchors.centerIn: parent;


        NumberAnimation on rotation{
            from: 0;
            to: 360;
            duration: 3600;
            loops: Animation.Infinite
        }
    }

}





