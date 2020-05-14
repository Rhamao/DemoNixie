import QtQuick 2.14
import QtQuick.Window 2.14


//Home page
Item {
    id: element

    width: 640
    height: 480
    property int smallMargin: 5
    property int mediumMargin: 10
    property int bigMargin: 20
    property var colorList: ["yellow", "red", "blue", "green", "pink"]
    //Background
    Rectangle
    {
        id: background
        color: "#000000"
        anchors.fill: parent
    }

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
        id: rectangle
        width: parent.width
        height: 60
        anchors {   top: title.bottom; topMargin: smallMargin;
                    left: parent.left; leftMargin: smallMargin;
                    right: parent.right; rightMargin: smallMargin }
        color : "white"
        anchors.horizontalCenterOffset: 5
        Repeater{
            model:colorList
            delegate: ColorSelector {
                colorModel: colorList[index]
                x: (width + smallMargin)*index
                anchors.verticalCenter: parent.verticalCenter
            }
        }

    }




}
