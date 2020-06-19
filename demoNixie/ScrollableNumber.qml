import QtQuick 2.0
import QtQuick.Controls 2.14

ItemDelegate {
    id: root
    height: fontSize*2
    property color fontColor: "white"
    property int fontSize: 20
    property int _text: index
    Text{
        id: text
        anchors.verticalCenter: parent.verticalCenter
        anchors.horizontalCenter: parent.horizontalCenter
        text: _text
        color: fontColor
        font.pointSize: fontSize
    }
}

