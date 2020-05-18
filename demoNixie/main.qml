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
            color: "#ffffff"
            font.family: "Segoe UI"
            anchors.horizontalCenter: parent.horizontalCenter
            font.pointSize: 11; font.bold: true
        }

        Rectangle{
            id: colorSelectionArea
            width: parent.width
            height: 60
            anchors {   top: title.bottom; topMargin: smallMargin }
            color : "white"

            Repeater{
                model:colorList
                delegate: ColorSelector {
                    colorModel: colorList[index]
                    x: (width + smallMargin)*index
                    anchors.verticalCenter: parent.verticalCenter
                }
            }
        }

        ScrollableClock {
            id: timeChangingArea
            fontColor: "black"
            backgroundColor: "white"
            fontSize: 20

        }

        Rectangle{
            id: timeArea
            width: parent.width
            height: 60
            anchors {top: colorSelectionArea.bottom; topMargin: smallMargin}
            color : "white"
            Timer {
                interval: 500; running: true; repeat: true
                onTriggered:{ time.text = new Date().toLocaleString(Qt.locale(), "hh:mm:ss")
                }
            }

            AppTimer {
                id: time
            }
        }

    }





}
