import QtQuick 2.14
import QtQuick.Window 2.14
import QtQuick.Controls 2.14
import DbgLink 1.0
import BleLink 1.0
import QtQuick.Dialogs 1.2
import QtGraphicalEffects 1.12
import QtQuick.Controls.Styles 1.4
import QtQuick.Extras 1.4



//Home page
Item {
    id: root

    width: 640
    height: 480
    property int smallMargin: 5
    property int mediumMargin: 10
    property int bigMargin: 20
    property var colorList: ["red", "white", "purple", "blue", "green", "yellow", "orange"]
    property string policeColor: "white"
    property string backgroundColor: "black"
    property bool btEnable: false
    property bool changingColor: false
    property int indexBuffer : 0
    property int colorSelectorsSize: 45

    function enableColorChanging(enabled){
        if(enabled){
            hoursArea.visible = true
            minsArea.visible = true
            secondsArea.visible = true
            colorCircleHighlighter.visible = true
            changingColor = true
        }else{
            hoursArea.visible = false
            minsArea.visible = false
            secondsArea.visible = false
            colorCircleHighlighter.visible = false
            changingColor = false
            rp.itemAt(indexBuffer).borderColor = colorList[indexBuffer]
        }
    }

    BleLink {
        id:ble
        Component.onCompleted: cpp.handleQmlBleInit(ble);

    }
    DbgLink {
        id:dbg
        Component.onCompleted: cpp.handleQmlDbgInit(dbg);
        onNewText:  {
            dbg.showToast(dbg.new_text, 1)
        }


    }

    MouseArea{
        anchors.fill: parent
        onClicked: {
            if(changingColor){
                enableColorChanging(false)
                console.log("click")
            }
        }
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
            width: colorList.length*(colorSelectorsSize + smallMargin)-smallMargin
            height: colorSelectorsSize
            anchors {top: title.bottom; topMargin: bigMargin; horizontalCenter: parent.horizontalCenter}
            color : "transparent"
            Repeater{
                id: rp
                model:colorList
                delegate: DemoNixieButton {
                    size: colorSelectorsSize
                    _color: colorList[index]
                    borderColor: colorList[index]
                    x: (colorSelectorsSize + smallMargin)*index
                    MouseArea {
                        id:ma
                        anchors.fill: parent
                        onClicked: {
                            console.log("[IN]Inddex selected " + index)
                            console.log("   Index color :            ", colorList[index])
                            console.log("   Index buffer :           ", indexBuffer)
                            console.log("   Index buffer color :     ", colorList[indexBuffer])
                            console.log("   changing color of time : ", changingColor)
                            borderColor = Qt.darker(colorList[index])
                            if(!changingColor){
                                indexBuffer = index
                                enableColorChanging(true)
                            }else if(indexBuffer === index){
                                enableColorChanging(false)
                                indexBuffer = index
                            }else if(indexBuffer !== index){
                                rp.itemAt(indexBuffer).borderColor = colorList[indexBuffer]
                                indexBuffer = index
                            }
                            console.log("[OUT]Index selected " + index)
                            console.log("   Index color :            ", colorList[index])
                            console.log("   Index buffer :           ", indexBuffer)
                            console.log("   Index buffer color :     ", colorList[indexBuffer])
                            console.log("   changing color of time : ", changingColor)
                        }
                        onReleased: {
                            _color = colorList[index]
                            console.log("released")
                        }
                    }
                }
            }
        }

        ScrollableClock {
            id: clock
            anchors{top: colorSelectionArea.bottom; horizontalCenter: parent.horizontalCenter; topMargin: mediumMargin}
            backgroundColor: root.backgroundColor
            fontSize: 60
            enableTimer: true
            Component.onCompleted: {
                setUtcButton._text = (clock.utc>=0)? "UTC\n+"+clock.utc+":00" : "UTC\n"+clock.utc+":00"
            }
        }

        ScrollableClock {
            id: fakeClock
            anchors{top: colorSelectionArea.bottom; horizontalCenter: parent.horizontalCenter; topMargin: mediumMargin}
            backgroundColor: root.backgroundColor
            fontSize: 60
            visible: false
            enableTimer: false
        }

        Row{
            anchors{left: clock.left; top: clock.top}
            spacing: clock.dotsWidth
            opacity: 0.25
            Rectangle{
                id:hoursArea
                width:clock.fontSize*2
                height: width
                radius: width
                color: "white"
                visible: false
                MouseArea{
                    anchors.fill: parent
                    onClicked: {
                        if(changingColor){
                            enableColorChanging(false)
                            console.log("hours clicked")
                            clock.fontColorHours = rp.itemAt(indexBuffer)._color
                        }
                    }
                }
            }

            Rectangle{
                id:minsArea
                width:clock.fontSize*2
                height: width
                radius: width
                color: "white"
                visible: false
                MouseArea{
                    anchors.fill: parent
                    onClicked: {
                        if(changingColor){
                            enableColorChanging(false)
                            console.log("mins clicked")
                            clock.fontColorMins = rp.itemAt(indexBuffer)._color

                        }
                    }
                }
            }

            Rectangle{
                id:secondsArea
                width:clock.fontSize*2
                height: width
                radius: width
                color: "white"
                visible: false
                MouseArea{
                    anchors.fill: parent
                    onClicked: {
                        if(changingColor){
                            enableColorChanging(false)
                            console.log("seconds clicked")
                            clock.fontColorSeconds = rp.itemAt(indexBuffer)._color
                        }
                    }
                }
            }
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
                    clock.resetLocalTime()
                    setUtcButton._text = (clock.utc>=0)? "UTC\n+"+clock.utc+":00" : "UTC\n"+clock.utc+":00"
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
                    enableColorChanging(false);
                    clock.visible = false
                    fakeClock.visible = true
                    fakeClock.setTime(clock.hours, clock.mins, clock.seconds)
                    timeButtons.visible = false
                    btSendButton.visible = false
                    timeSetPlusButtons.visible = true
                    timeSetMinusButtons.visible = true
                    colorPicker.visible = false
                    timeButtons.anchors.topMargin = timeButtons.anchors.topMargin + 110
                    fakeClock.fontColorHours = clock.fontColorHours
                    fakeClock.fontColorMins = clock.fontColorMins
                    fakeClock.fontColorSeconds = clock.fontColorSeconds
                    console.log("Clock visible ;", clock.visible)
                    console.log("FakeClock  visible;", fakeClock.visible)
                }
            }

            DemoNixieButton{
                id: setUtcButton
                _color: "#333333"
                size: 50
                fontSize: 14
                fontBold: true
                fontColor: "white"
                onClicked: {
                    enableColorChanging(false)
                    clock.visible = false
                    utcArea.visible = true
                    utcSetPlusButtons.visible = true
                    utcSetMinusButton.visible = true
                    timeButtons.visible = false
                    btSendButton.visible = false
                    colorPicker.visible = false
                    utcListView.currentIndex=clock.utc+12
                    utcListView.positionViewAtIndex(clock.utc+12, ListView.Center);
                }
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
                    setUtcButton._text="UTC\n+?"
                    clock.setTime(fakeClock.hours, fakeClock.mins, fakeClock.seconds)
                    timeButtons.visible = true
                    btSendButton.visible = true
                    timeSetPlusButtons.visible = false
                    timeSetMinusButtons.visible = false
                    timeButtons.anchors.topMargin = timeButtons.anchors.topMargin - 110
                    clock.visible = true
                    colorPicker.visible = true
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
                    colorPicker.visible = true
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
            _color: (!btEnable) ? "#333333" : "#000066"
            iconSource: "images/bluetoothIconWhite.png"
            icon.color: "white"
            onClicked: {
               if(!btEnable){
                   btEnable = true
                   _color = "#660000"
                   ble.runDiscovery()
               }
               else{
                   btEnable = false
                   _color = "#333333"
                   ble.stopDiscovery()
                }
                console.log("Color", _color)
            }
            states: State {
                name: "BLEconnected"
                when: ble.connected
                PropertyChanges {
                    target: btConnectButton
                    _color: "#000066"
                }
            }
            Behavior on rotation {
                RotationAnimation{
                    duration: 10000

                }
            }

        }

        DemoNixieButton{
            id:btSendButton
            anchors{top: timeButtons.bottom; horizontalCenter: parent.horizontalCenter; topMargin: bigMargin}
            size:60
            _color: "#333333"
            iconSource: "images/senbByBluetoothWhite.png"
            icon.color: "white"
            onClicked: {
                ble.writeTime(clock.hours,clock.mins,clock.seconds)
                ble.writeAnimation(false, clock.fontColorHours, 0, clock.fontColorMins, 0, clock.fontColorSeconds, 0)
            }
        }


        Rectangle{
            id:utcArea
            color: "black"
            width: 60*2
            height: 60*2
            anchors{top: colorSelectionArea.bottom; horizontalCenter: parent.horizontalCenter; topMargin: mediumMargin}
            visible: false
            ScrollView {
                id: utcScrollView
                anchors.verticalCenter: parent.verticalCenter
                width: parent.width
                height: parent.height
                clip: true
                enabled: false
                ListView {
                    id:utcListView
                    model: 27
                    delegate: ScrollableNumber {
                        _text: index - 12
                        fontColor: "white"
                        fontSize: 60
                    }
                }
            }
        }

        Row{
            id:utcSetPlusButtons
            anchors{top: clock.bottom; horizontalCenter: parent.horizontalCenter; topMargin: mediumMargin}
            spacing: timeSetPlusButtons.spacing
            visible: false

            DemoNixieButton{
                id: setUtcButton2
                _color: "#333333"
                size: 50
                _text:"Set\nUTC"
                fontSize: 14
                fontBold: true
                fontColor: "white"
                onClicked:{
                    clock.utc=utcListView.currentIndex-12
                    clock.setUtcTime()
                    clock.visible = true
                    utcArea.visible = false
                    utcSetPlusButtons.visible = false
                    utcSetMinusButton.visible = false
                    timeButtons.visible = true
                    btSendButton.visible = true
                    colorPicker.visible = true
                    setUtcButton._text = (clock.utc>=0)? "UTC\n+"+clock.utc+":00" : "UTC\n"+clock.utc+":00"
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
                    if(utcListView.currentIndex<26)
                        utcListView.currentIndex++
                    console.log("UTCindex",  utcListView.currentIndex)
                }
            }

            DemoNixieButton{
                id: setUtcCancelButton
                _color: "#333333"
                size: 50
                iconSource: "images/crossWhite.png"
                fontColor: "white"
                onClicked:{
                    clock.visible = true
                    utcArea.visible = false
                    utcSetPlusButtons.visible = false
                    utcSetMinusButton.visible = false
                    timeButtons.visible = true
                    btSendButton.visible = true
                    colorPicker.visible = true
                }
            }

        }

        DemoNixieButton{
            id:utcSetMinusButton
            size:45
            anchors{top: utcSetPlusButtons.bottom; horizontalCenter: parent.horizontalCenter; topMargin: smallMargin*2}
            _color: "#333333"
            _text:"-"
            fontSize: 25
            fontColor: "#bbbbbb"
            autoRepeat: true
            visible: false
            onClicked:{
                if(utcListView.currentIndex>0)
                    utcListView.currentIndex--
                console.log("UTCindex",  utcListView.currentIndex)
            }
        }

        Row{
            id:colorPicker
            anchors{top:btSendButton.bottom; topMargin: 50; left:parent.left; horizontalCenter: parent.horizontalCenter; leftMargin: smallMargin}
            Rectangle{
                id: colorCircle
                border.width: 5
                width: 190; height: width; radius: width;
                color: Qt.rgba(rgbSliders.redCode/255, rgbSliders.greenCode/255, rgbSliders.blueCode/255, 1)
                Rectangle{
                    id:colorCircleHighlighter
                    anchors.centerIn: colorCircle
                    width:colorCircle.width+10
                    height: width
                    radius: width
                    color: "white"
                    opacity: 0.25
                    visible: false
                }
                MouseArea{
                    anchors.fill: parent
                    onClicked: {
                        console.log("Color picker circle clicked")
                        if(changingColor){
                            console.log("   Color at index " + indexBuffer + " has been changed to " + colorCircle.color)
                            colorList[indexBuffer] = Qt.rgba(rgbSliders.redCode/255, rgbSliders.greenCode/255, rgbSliders.blueCode/255, 1)
                            rp.itemAt(indexBuffer)._color = colorList[indexBuffer]
                            enableColorChanging(false)
                        }
                    }
                }
            }
            RgbSliders{
                id:rgbSliders
            }
        }

    }
}
