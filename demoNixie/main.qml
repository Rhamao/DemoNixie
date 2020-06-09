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
                    clock.pause = !clock.pause
                    clock.visible = !clock.visible
                    fakeClock.visible = !fakeClock.visible
                    fakeClock.hours = clock.hours
                    fakeClock.mins = clock.mins
                    fakeClock.seconds = clock.seconds
                    timeSetPlusButtons.visible = !timeSetPlusButtons.visible
                    timeSetMinusButtons.visible = !timeSetMinusButtons.visible
                    if(clock.pause) timeButtons.anchors.topMargin = timeButtons.anchors.topMargin + 100
                    if(!clock.pause) timeButtons.anchors.topMargin = timeButtons.anchors.topMargin - 100
                    console.log("Clock visible ;", clock.visible)
                    console.log("FakeClock  :", fakeClock.scrollLock)
                    console.log("Pause ;", clock.pause)
                    console.log("Scrolling enabled :", clock.scrollLock)
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
                    if((clock.hours+clock.hoursOffset)<24){
                        clock.hoursOffset = clock.hoursOffset + 1
                        fakeClock.hours = clock.hours+clock.hoursOffset
                    }
                    console.log("hours", clock.hours)
                    console.log("offset", clock.hoursOffset)
                    console.log("hours + offset", (clock.hours+clock.hoursOffset))
                }
            }

            DemoNixieButton{
                size:40
                _color: "#333333"
                text:"+"
                fontSize: 16
                onClicked:{
                    if((clock.mins+clock.minsOffset)<60){
                        clock.minsOffset = clock.minsOffset + 1
                        fakeClock.mins = clock.mins+clock.minsOffset
                    }
                    console.log("mins", clock.mins)
                    console.log("offset", clock.minsOffset)
                    console.log("mins + offset", (clock.mins+clock.minsOffset))
                }
            }

            DemoNixieButton{
                size:40
                _color: "#333333"
                text:"+"
                fontSize: 16
                onClicked:{
                    if((clock.seconds+clock.secondsOffset)<60){
                        clock.secondsOffset = clock.secondsOffset + 1
                        fakeClock.seconds = clock.seconds+clock.secondsOffset
                    }
                    console.log("seconds", clock.seconds)
                    console.log("offset", clock.secondsOffset)
                    console.log("seconds + offset", (clock.seconds+clock.secondsOffset))
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
                    if((clock.hours+clock.hoursOffset)>0){
                        clock.hoursOffset = clock.hoursOffset - 1
                        fakeClock.hours = clock.hours+clock.hoursOffset
                    }
                    console.log("hours", clock.hours)
                    console.log("offset", clock.hoursOffset)
                    console.log("hours + offset", (clock.hours+clock.hoursOffset))
                }
            }

            DemoNixieButton{
                size:40
                _color: "#333333"
                text:"-"
                fontSize: 16
                onClicked:{
                    if((clock.mins+clock.minsOffset)>0){
                        clock.minsOffset = clock.minsOffset - 1
                        fakeClock.mins = clock.mins+clock.minsOffset
                    }
                    console.log("mins", clock.mins)
                    console.log("offset", clock.minsOffset)
                    console.log("mins + offset", (clock.mins+clock.minsOffset))
                }
            }

            DemoNixieButton{
                size:40
                _color: "#333333"
                text:"-"
                fontSize: 16
                onClicked:{
                    if((clock.seconds+clock.secondsOffset)>0){
                        clock.secondsOffset = clock.secondsOffset - 1
                        fakeClock.hours = clock.hours+clock.hoursOffset
                    }
                    console.log("seconds", clock.seconds)
                    console.log("offset", clock.secondsOffset)
                    console.log("seconds + offset", (clock.seconds+clock.secondsOffset))
                }
            }
        }
    }
}
