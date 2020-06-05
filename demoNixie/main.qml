import QtQuick 2.14
import QtQuick.Window 2.14
import QtQuick.Controls 2.14


//Home page
Item {
    id: element

    width: 640
    height: 480
    property int smallMargin: 5
    property int mediumMargin: 10
    property int bigMargin: 20
    property int bigFontSize: 20
    property var colorList: ["red", "pink", "purple", "blue", "green", "yellow", "orange"]
    property string policeColor: "white"
    property string backgroundColor: "black"
    property int hour: 0
    property int minute: 0
    property int second: 0
    property var iconList: ["images/reset.png", "", ""]
    property string utc: "  UTC\n+2:00"
    property var buttonTextList: ["", "", utc]

    //Background
    Rectangle
    {
        id: background
        color: "#000000"
        anchors.fill: parent
    }

    //Area of design with a smallMargin to avoid icons
    //touching the border
    Rectangle{
        id: designArea
        color: "black"
        anchors.fill: parent
        anchors{left: parent.left; leftMargin: smallMargin;
                right: parent.right; rightMargin: smallMargin}
        //Title
        Text {
            id: title
            text: "DemoNixie"
            y: 30
            color: "white"
            font.family: "Segoe UI"
            anchors.horizontalCenter: parent.horizontalCenter
            font.pointSize: 40;
            font.bold: true
        }

        Rectangle{
            id: colorSelectionArea
            width: parent.width
            height: 60
            anchors {   top: title.bottom; topMargin: mediumMargin}
            color : backgroundColor

            Repeater{
                model:colorList
                anchors{horizontalCenter: parent.horizontalCenter}
                delegate: ColorSelector {
                    _color: colorList[index]
                    x: (width + smallMargin)*index
                    //anchors.horizontalCenter: parent.horizontalCenter
                    //anchors.verticalCenter: parent.verticalCenter
                }
            }
        }

        ScrollableClock {
            id: timeChangingArea
            anchors{top: colorSelectionArea.bottom; horizontalCenter: parent.horizontalCenter; topMargin: mediumMargin}
            fontColor: policeColor
            backgroundColor: element.backgroundColor
            fontSize: 60
        }

        Rectangle{
            id: timeArea
            width: parent.width
            height: 60
            anchors {top: colorSelectionArea.bottom; topMargin: smallMargin}
            color : "white"
            visible: false
            Timer {
                interval: 1000; running: true; repeat: true
                onTriggered:{
                    //time.text = new Date().toLocaleString(Qt.locale(), "hh:mm:ss")
                    hour = new Date().toLocaleString(Qt.locale(), "hh")
                    minute = new Date().toLocaleString(Qt.locale(), "mm")
                    second = new Date().toLocaleString(Qt.locale(), "ss")
                    timeChangingArea.hours = hour
                    timeChangingArea.mins = minute
                    timeChangingArea.seconds = second
                }
            }

            AppTimer {
                id: time
            }
        }

        ButtonGroup {
            buttons: row.children
        }

        Row {
            id: row
            anchors{top: timeArea.bottom; horizontalCenter: parent.horizontalCenter; topMargin: 100}
            spacing: 40

            Repeater{
                model:iconList
                anchors{horizontalCenter: parent.horizontalCenter}
                delegate: DemoNixieButton {
                    _color: "#333333"
                    size: 50
                    _text: buttonTextList[index]
                    iconSource: iconList[index]
                    fontSize: 10
                }
            }
        }

    }





}
