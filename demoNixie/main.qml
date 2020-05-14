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
    property int timeScrollerWidth: 65
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

        Rectangle{
            id: timeChangingArea
            width: 250
            height: 60
            anchors {top: timeArea.bottom; topMargin: smallMargin}
            color : "white"
            ScrollView {
                id: hour
                width: timeScrollerWidth
                height: timeChangingArea.height
                font.pointSize: bigFontSize
                clip: true
                anchors {verticalCenter: parent.verticalCenter}
                ListView {
                    id: houListView
                    model: 24
                    delegate: ItemDelegate {
                        text: index
                    }
                }
            }
            Text {
                id: dots
                font.pointSize: bigFontSize
                text: qsTr(":")
                anchors{verticalCenter: parent.verticalCenter; left: hour.right }
            }
            ScrollView {
                id: min
                width: timeScrollerWidth
                height: timeChangingArea.height
                font.pointSize: bigFontSize
                clip: true
                anchors {verticalCenter: parent.verticalCenter; left: dots.right; leftMargin: 23}
                ListView {
                    id: minListView
                    model: 60
                    delegate: ItemDelegate {
                        text: index
                    }
                }
            }
            Text {
                id: dots2
                font.pointSize: bigFontSize
                text: qsTr(":")
                anchors{verticalCenter: parent.verticalCenter; left: min.right }
            }
            ScrollView {
                id: second
                width: timeScrollerWidth
                height: timeChangingArea.height
                font.pointSize: bigFontSize
                clip: true
                anchors {verticalCenter: parent.verticalCenter; left: dots2.right; leftMargin: 23}
                ListView {
                    id: secondListView
                    model: 60
                    delegate: ItemDelegate {
                        text: index
                    }
                }
            }
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
