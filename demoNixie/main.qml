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
    property string utc: "UTC\n+2:00"
    property var buttonTextList: ["", " Set\nTime", utc]
    property bool btEnable: false

    Loader
    {
      id: myLoader
      source: "ScrollableClock.qml"
    }

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
                right: parent.right; rightMargin: smallMargin
                bottomMargin: smallMargin; topMargin: smallMargin}
        Text {
            id: title
            text: "DemoNixie"
            y: 30
            color: "white"
            font.family: "Segoe UI"
            anchors{horizontalCenter:  parent.horizontalCenter; top: parent.top}
            font.pointSize: 40;
            font.bold: true
        }

        Rectangle{
            id: colorSelectionArea
            width: parent.width
            height: 45
            anchors {   top: title.bottom; topMargin: bigMargin}
            color : backgroundColor
            Repeater{
                model:colorList
                anchors{horizontalCenter: parent.horizontalCenter}
                delegate: ColorSelector {
                    _color: colorList[index]
                    x: (45 + smallMargin)*index
                }
            }
        }

        ScrollableClock {
            id: clock
            anchors{top: colorSelectionArea.bottom; horizontalCenter: parent.horizontalCenter; topMargin: mediumMargin}
            fontColor: policeColor
            backgroundColor: element.backgroundColor
            fontSize: 60
            enableTimer: true
        }

        ScrollableClock {
            id: fakeClock
            anchors{top: colorSelectionArea.bottom; horizontalCenter: parent.horizontalCenter; topMargin: mediumMargin}
            fontColor: policeColor
            backgroundColor: element.backgroundColor
            fontSize: 60
            visible: false
            enableTimer: false
        }

        Row {
            id: timeButtons
            anchors{top: clock.bottom; horizontalCenter: parent.horizontalCenter; topMargin: mediumMargin}
            spacing: 40
            DemoNixieButton{
                id: resetTimeButton
                _color: "#333333"
                size: 50
                iconSource: "images/resetWhite.png"
                icon.color: "white"
                fontSize: 16
                onClicked: {
                    clock.resetTime()
                }
            }

            DemoNixieButton{
                id: setTimeButton
                _color: "#333333"
                size: 50
                _text:"Set\nTime"
                fontSize: 14
                fontBold: true
                fontColor: "white"
                onClicked:{
                    clock.visible = false
                    fakeClock.visible = true
                    fakeClock.setTime(clock.hours, clock.mins, clock.seconds)
                    timeButtons.visible = false
                    btSendButton.visible = false
                    timeSetPlusButtons.visible = true
                    timeSetMinusButtons.visible = true
                    timeButtons.anchors.topMargin = timeButtons.anchors.topMargin + 110
                    console.log("Clock visible ;", clock.visible)
                    console.log("FakeClock  visible;", fakeClock.visible)
                }
            }

            DemoNixieButton{
                id: setUtcButton
                _color: "#333333"
                size: 50
                _text: utc
                fontSize: 14
                fontBold: true
                fontColor: "white"
            }
        }


        Row {
            id: timeSetPlusButtons
            anchors{top: clock.bottom; horizontalCenter: parent.horizontalCenter; topMargin: mediumMargin}
            spacing: 30
            visible: false

            DemoNixieButton{
                id: setTimeButton2
                _color: "#333333"
                size: 50
                _text:"Set\nTime"
                fontSize: 14
                fontBold: true
                fontColor: "white"
                onClicked:{
                    clock.setTime(fakeClock.hours, fakeClock.mins, fakeClock.seconds)
                    timeButtons.visible = true
                    btSendButton.visible = true
                    timeSetPlusButtons.visible = false
                    timeSetMinusButtons.visible = false
                    timeButtons.anchors.topMargin = timeButtons.anchors.topMargin - 110
                    clock.visible = true
                    fakeClock.visible = false
                    console.log("Clock visible ;", clock.visible)
                    console.log("FakeClock  visible;", fakeClock.visible)
                }
            }

            DemoNixieButton{
                size:45
                _color: "#333333"
                _text:"+"
                fontSize: 25
                fontColor: "#bbbbbb"
                autoRepeat: true
                onClicked:{
                    if(fakeClock.hours<23)
                        fakeClock.hours = fakeClock.hours + 1
                    console.log("hours", fakeClock.hours)
                }
            }

            DemoNixieButton{
                size:45
                _color: "#333333"
                _text:"+"
                fontSize: 25
                fontColor: "#bbbbbb"
                autoRepeat: true
                onClicked:{
                    if(fakeClock.mins<59)
                        fakeClock.mins = fakeClock.mins + 1
                    console.log("mins", fakeClock.mins)
                }
            }

            DemoNixieButton{
                size:45
                _color: "#333333"
                _text:"+"
                fontSize: 25
                fontColor: "#bbbbbb"
                autoRepeat: true
                onClicked:{
                    if(fakeClock.seconds<59)
                        fakeClock.seconds = fakeClock.seconds + 1
                    console.log("seconds", fakeClock.seconds)
                }
            }

            DemoNixieButton{
                id: setTimeCancelButton
                _color: "#333333"
                size: 50
                iconSource: "images/crossWhite.png"
                fontColor: "white"
                onClicked:{
                    timeButtons.visible = true
                    btSendButton.visible = true
                    timeSetPlusButtons.visible = false
                    timeSetMinusButtons.visible = false
                    timeButtons.anchors.topMargin = timeButtons.anchors.topMargin - 110
                    clock.visible = true
                    fakeClock.visible = false
                    console.log("Clock visible ;", clock.visible)
                    console.log("FakeClock  visible;", fakeClock.visible)
                }
            }
        }

        Row {
            id: timeSetMinusButtons
            anchors{top: timeSetPlusButtons.bottom; horizontalCenter: parent.horizontalCenter; topMargin: smallMargin}
            spacing: 30
            visible: false
            DemoNixieButton{
                size:45
                _color: "#333333"
                _text:"-"
                fontSize: 25
                fontColor: "#bbbbbb"
                autoRepeat: true
                onClicked:{
                    if(fakeClock.hours>0)
                        fakeClock.hours = fakeClock.hours - 1
                    console.log("hours", fakeClock.hours)
                }
            }

            DemoNixieButton{
                size:45
                _color: "#333333"
                _text:"-"
                fontSize: 25
                fontColor: "#bbbbbb"
                autoRepeat: true
                onClicked:{
                    if(fakeClock.mins>0)
                        fakeClock.mins = fakeClock.mins - 1
                    console.log("mins", fakeClock.mins)
                }
            }

            DemoNixieButton{
                size:45
                _color: "#333333"
                _text:"-"
                fontSize: 25
                fontColor: "#bbbbbb"
                autoRepeat: true
                onClicked:{
                    if(fakeClock.seconds>0)
                        fakeClock.seconds = fakeClock.seconds - 1
                    console.log("seconds", fakeClock.seconds)
                }
            }
        }

        DemoNixieButton{
            id:btConnectButton
            anchors{left: parent.left; top: parent.top}
            size:50
            _color: "#333333"
            iconSource: "images/bluetoothIconWhite.png"
            icon.color: "white"
            onClicked: {
               if(!btEnable){
                   btEnable = true
                   _color = "#000066"
               }
               else{
                   btEnable = false
                   _color = "#333333"
                }
                console.log("Color", _color)
            }
        }

        DemoNixieButton{
            id:btSendButton
            anchors{top: timeButtons.bottom; horizontalCenter: parent.horizontalCenter; topMargin: bigMargin}
            size:60
            _color: "#333333"
            iconSource: "images/senbByBluetoothWhite.png"
            icon.color: "white"
        }
    }
}
