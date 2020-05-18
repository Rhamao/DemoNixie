import QtQuick 2.14
import QtQuick.Window 2.14
import QtQuick.Controls 2.14


//Home page
Rectangle{
    id: root
    width: fontSize*8
    height: fontSize*2
    property color backgroundColor: "black"
    property color fontColor: "white"
    property int fontSize: 20
    property int timeScrollerWidth: fontSize*2
    anchors {top: timeArea.bottom; topMargin: smallMargin}
    color : backgroundColor
    ScrollView {
        id: hour
        width: timeScrollerWidth
        height: parent.height
        clip: true
        anchors {verticalCenter: parent.verticalCenter; right: dots.left}
        ListView {
            id: houListView
            model: 24
            delegate: ScrollableNumber {
                fontColor: root.fontColor
                fontSize: root.fontSize
            }
        }
    }
    Text {
        id: dots
        font.pointSize: fontSize
        color: fontColor
        text: qsTr(":")
        anchors{verticalCenter: parent.verticalCenter; right: min.left}
    }
    ScrollView {
        id: min
        width: timeScrollerWidth
        height: timeChangingArea.height
        clip: true
        anchors {verticalCenter: parent.verticalCenter; horizontalCenter: parent.horizontalCenter}
        ListView {
            id: minListView
            model: 60
            delegate: ScrollableNumber {
                fontColor: root.fontColor
                fontSize: root.fontSize
            }
        }
    }
    Text {
        id: dots2
        font.pointSize: fontSize
        color: fontColor
        text: qsTr(":")
        anchors{verticalCenter: parent.verticalCenter; left: min.right}
    }
    ScrollView {
        id: second
        width: timeScrollerWidth
        height: timeChangingArea.height
        clip: true
        anchors {verticalCenter: parent.verticalCenter; left: dots2.right}
        ListView {
            id: secondListView
            model: 60
            delegate: ScrollableNumber {
                fontColor: root.fontColor
                fontSize: root.fontSize
            }
        }
    }
}
