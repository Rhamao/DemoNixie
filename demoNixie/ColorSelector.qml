import QtQuick 2.14
import QtQuick.Window 2.14


//Home page
Rectangle{

    id: root
    property color colorModel: "red"
    property int size: 45
    width : size
    height: width
    color : (ma.containsMouse) ? Qt.lighter(colorModel) : colorModel
    radius: width
    MouseArea {
        id:ma
        anchors.fill: parent
        hoverEnabled: true
        onHoveredChanged: {
            console.log("hovered :", ma.containsMouse)
        }
        //onClicked: rectangle.color = colorModel
    }
}
