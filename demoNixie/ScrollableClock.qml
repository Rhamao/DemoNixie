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
    color: backgroundColor
    property int seconds: 0
    property int hours: 0
    property int mins: 0
    property int delay: 0
    ScrollView {
        id: hour
        width: timeScrollerWidth
        height: parent.height
        clip: true
        anchors {verticalCenter: parent.verticalCenter; right: dots.left}
        ListView {
            id: hourListView
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
        height: parent.height
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
        height: parent.height
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

    Rectangle{
        id: timer
        width: parent.width
        height: 60
        visible: false
        Timer {
            interval: 1000; running: true; repeat: true
            onTriggered:{
                hourListView.positionViewAtIndex(new Date().toLocaleString(Qt.locale(), "hh"), ListView.Center)
                minListView.positionViewAtIndex(new Date().toLocaleString(Qt.locale(), "mm"), ListView.Center)
                secondListView.positionViewAtIndex(new Date().toLocaleString(Qt.locale(), "ss"), ListView.Center)
            }
        }
    }


}
