import QtQuick 2.0
import QtQuick.Controls 2.14

ItemDelegate {
    id: root
    height: fontSize*2
    property color fontColor: "white"
    property int fontSize: 20
    Text{
        id: text
        anchors.horizontalCenter: parent.horizontalCenter
        text: index
        color: fontColor
        font.pointSize: fontSize
    }
}

