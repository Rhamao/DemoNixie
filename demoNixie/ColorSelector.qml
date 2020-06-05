import QtQuick 2.14
import QtQuick.Window 2.14


//Home page
Rectangle{
    id: root
    property color _color: "red"
    property int size: 45
    width : size
    height: width
    color : (ma.containsMouse) ? Qt.lighter(_color) : _color
    radius: width
    MouseArea {
        id:ma
        anchors.fill: parent
        hoverEnabled: true
        onHoveredChanged: {
            console.log("hovered :", ma.containsMouse)
        }
    }
}
