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
    property var buttonTextList: ["", " Set\nTime", utc]

    //Background
    Rectangle
    {
        id: background
        color: "#000000"
        anchors.fill: parent
    }

    Rectangle{
        id: designArea
        color: "black"
        anchors.fill: parent
        anchors{left: parent.left; leftMargin: smallMargin;
                right: parent.right; rightMargin: smallMargin}
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
            anchors {   top: title.bottom; topMargin: bigMargin}
            color : backgroundColor
            Repeater{
                model:colorList
                anchors{horizontalCenter: parent.horizontalCenter}
                delegate: ColorSelector {
                    _color: colorList[index]
                    x: (size + smallMargin)*index
                }
            }
        }

        ScrollableClock {
            id: clock
            anchors{top: colorSelectionArea.bottom; horizontalCenter: parent.horizontalCenter}
            fontColor: policeColor
            backgroundColor: element.backgroundColor
            fontSize: 60
            enableTimer: true
        }

        ScrollableClock {
            id: fakeClock
            anchors{top: colorSelectionArea.bottom; horizontalCenter: parent.horizontalCenter}
            fontColor: policeColor
            backgroundColor: element.backgroundColor
            fontSize: 60
            visible: false
            enableTimer: false
        }

        Row {
            id: timeButtons
            anchors{top: clock.bottom; horizontalCenter: parent.horizontalCenter; topMargin: bigMargin}
            spacing: 40
            DemoNixieButton{
                id: resetTimeButton
                _color: "#333333"
                size: 50
                iconSource: "images/reset.png"
                fontSize: 16
            }

            DemoNixieButton{
                id: setTimeButton
                _color: "#333333"
                size: 50
                _text:"  Set\nTime"
                fontSize: 16
                onClicked:{
                    clock.scrollLock = !clock.scrollLock
                    clock.visible = !clock.visible
                    fakeClock.visible = !fakeClock.visible
                    fakeClock.hours = 0
                    fakeClock.mins = 0
                    fakeClock.seconds = 0
                    timeSetPlusButtons.visible = !timeSetPlusButtons.visible
                    timeSetMinusButtons.visible = !timeSetMinusButtons.visible
                    if(!clock.visible) timeButtons.anchors.topMargin = timeButtons.anchors.topMargin + 100
                    if(clock.visible) timeButtons.anchors.topMargin = timeButtons.anchors.topMargin - 100
                    console.log("Clock visible ;", clock.visible)
                    console.log("FakeClock  visible;", fakeClock.visible)
                    console.log("Clock pause ;", clock.pause)
                }
            }

            DemoNixieButton{
                id: setUtcButton
                _color: "#333333"
                size: 50
                _text: utc
                fontSize: 16
            }
        }


        Row {
            id: timeSetPlusButtons
            anchors{top: clock.bottom; horizontalCenter: parent.horizontalCenter; topMargin: bigMargin}
            spacing: 100
            visible: false
            DemoNixieButton{
                size:40
                _color: "#333333"
                text:"+"
                fontSize: 16
                onClicked:{
                    if(fakeClock.hours<23)
                        fakeClock.hours = fakeClock.hours + 1
                    console.log("hours", fakeClock.hours)
                }
            }

            DemoNixieButton{
                size:40
                _color: "#333333"
                text:"+"
                fontSize: 16
                onClicked:{
                    if(fakeClock.mins<59)
                        fakeClock.mins = fakeClock.mins + 1
                    console.log("mins", fakeClock.mins)
                }
            }

            DemoNixieButton{
                size:40
                _color: "#333333"
                text:"+"
                fontSize: 16
                onClicked:{
                    if(fakeClock.seconds<59)
                        fakeClock.seconds = fakeClock.seconds + 1
                    console.log("seconds", fakeClock.seconds)
                }
            }
        }

        Row {
            id: timeSetMinusButtons
            anchors{top: timeSetPlusButtons.bottom; horizontalCenter: parent.horizontalCenter; topMargin: smallMargin}
            spacing: 100
            visible: false
            DemoNixieButton{
                size:40
                _color: "#333333"
                text:"-"
                fontSize: 16
                onClicked:{
                    if(fakeClock.hours>0)
                        fakeClock.hours = fakeClock.hours - 1
                    console.log("hours", fakeClock.hours)
                }
            }

            DemoNixieButton{
                size:40
                _color: "#333333"
                text:"-"
                fontSize: 16
                onClicked:{
                    if(fakeClock.mins>0)
                        fakeClock.mins = fakeClock.mins - 1
                    console.log("mins", fakeClock.mins)
                }
            }

            DemoNixieButton{
                size:40
                _color: "#333333"
                text:"-"
                fontSize: 16
                onClicked:{
                    if(fakeClock.seconds>0)
                        fakeClock.seconds = fakeClock.seconds - 1
                    console.log("seconds", fakeClock.seconds)
                }
            }
        }
    }
}
