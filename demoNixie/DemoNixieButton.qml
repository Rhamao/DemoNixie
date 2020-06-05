import QtQuick 2.14
import QtQuick.Window 2.14
import QtQuick.Controls 2.14


//Home page
Button {
    id: root
    property color _color: "white"
    property int size: 45
    property string iconSource: ""
    property string _text: ""
    property int fontSize : 5
    width : size
    height: size
    icon.source: iconSource
    icon.color: "white"
    //text: qsTr(_text)
    font.pointSize: fontSize

    background: Rectangle {
        id:buttonBackground
        width : size
        height: size
        radius: size
        opacity: enabled ? 1 : 0.3
        border.color: root.down ? "#333333" : Qt.lighter("#333333")
        border.width: 3
        color: root.down ? _color : Qt.lighter(_color)
        Text {
            id: mytext
            anchors{horizontalCenter: parent.horizontalCenter; verticalCenter: parent.verticalCenter}
            text: _text
            font.pointSize: fontSize
            color: "#838383"
        }
    }

    /*contentItem: Text {
        text: root.text
        font: root.font
        opacity: enabled ? 1.0 : 0.3
        color: root.down ? "white" : "white"
        horizontalAlignment: Text.AlignHCenter
        verticalAlignment: Text.AlignVCenter
        elide: Text.ElideRight
    }*/
}
