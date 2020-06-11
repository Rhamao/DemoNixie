import QtQuick 2.14
import QtQuick.Window 2.14
import QtQuick.Controls 2.14


//Home page
Button {
    id: root
    property color _color: "white"
    property int size: 45
    property string _text: ""
    property int fontSize : 5
    property color fontColor: "#838383"
    property bool fontBold: false
    property string iconSource: ""
    width : size
    height: size

    background: Rectangle {
        id:buttonBackground
        width : size
        height: size
        radius: size
        opacity: enabled ? 1 : 0.3
        border.color: Qt.lighter(_color)
        border.width: 3
        color: !root.down ? _color : Qt.lighter(_color)
        /*Text {
            id: mytext
            anchors{horizontalCenter: parent.horizontalCenter; verticalCenter: parent.verticalCenter}
            text: _text
            font.pointSize: fontSize
            color: fontColor
            font.bold: true
            font.family: "Segoe UI"
        }*/
        Image {
            width: size-0.4*size
            height: size-0.4*size
            anchors{centerIn: parent}
            source: iconSource
        }
    }

    contentItem: Text {
        text: _text
        font.family: "Segoe UI"
        font.pointSize: fontSize
        font.bold: fontBold
        opacity: enabled ? 1.0 : 0.3
        color: !root.down ? fontColor : Qt.lighter(fontColor)
        horizontalAlignment: Text.AlignHCenter
        verticalAlignment: Text.AlignVCenter
        elide: Text.ElideRight
        /*Image {
            width:size-10
            height: size-10
            anchors{centerIn: panret}
            source: iconSource
        }*/
    }


}
