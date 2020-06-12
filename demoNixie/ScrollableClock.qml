import QtQuick 2.14
import QtQuick.Window 2.14
import QtQuick.Controls 2.14
import TimeZone 1.0


//Home page
Rectangle{
    id: root
    width: fontSize*8
    height: fontSize*2
    property color backgroundColor: "black"
    property color fontColor: "white"
    property int fontSize: 20
    property int timeScrollerWidth: fontSize*2
    color: backgroundColor
    property int seconds: 0
    property int hours: 0
    property int mins: 0
    property int delay: 0
    property bool enableTimer: true
    property int utc: -13

    TimeZone{
        id:tiZone
        Component.onCompleted: cpp.handleTimeZoneInit(timeZone);
    }

    ScrollView {
        id: hour
        width: timeScrollerWidth
        height: parent.height
        clip: true
        anchors {verticalCenter: parent.verticalCenter; right: dots.left}
        ScrollBar.horizontal.policy: ScrollBar.AlwaysOff
        ScrollBar.vertical.policy: ScrollBar.AlwaysOff
        enabled: false




        ListView {
            id: hourListView
            model: 24
            currentIndex: hours
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
        //text: tiZone.timeZone
        text: qsTr(":")
        anchors{verticalCenter: parent.verticalCenter; right: min.left}
    }
    ScrollView {
        id: min
        width: timeScrollerWidth
        height: parent.height
        clip: true
        anchors {verticalCenter: parent.verticalCenter; horizontalCenter: parent.horizontalCenter}
        ScrollBar.horizontal.policy: ScrollBar.AlwaysOff
        ScrollBar.vertical.policy: ScrollBar.AlwaysOff
        enabled: false
        ListView {
            id: minListView
            model: 60
            currentIndex: mins
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
        ScrollBar.horizontal.policy: ScrollBar.AlwaysOff
        ScrollBar.vertical.policy: ScrollBar.AlwaysOff
        enabled: false
        ListView {
            id: secondListView
            model: 60
            currentIndex: seconds
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
        enabled: enableTimer
        Timer {

            interval: 1000; running: enableTimer; repeat: true
            Component.onCompleted:{
                if(enableTimer){
                    //const test = new Date().setUTCHours(5)
                    //test
                    setTime(new Date().toLocaleString(Qt.locale(), "hh"),
                            new Date().toLocaleString(Qt.locale(), "mm"),
                            new Date().toLocaleString(Qt.locale(), "ss"))

                }
            }

            onTriggered:{
                if(enableTimer){
                    seconds = seconds + 1
                    if(seconds>59){
                        secondListView.positionViewAtBeginning()
                        seconds = 0
                        mins = mins + 1;
                    }
                    if(mins>59){
                        mins = 0
                        hours = hours + 1
                    }
                    if(hours>23){
                        hours=0
                    }
                }
            }
        }
    }

    function setTime(h,m,s){
        hours = h
        if(utc>=-18 && utc<=14){
            hours = hours - tiZone.timeZone + utc
            if(hours<0)
                hours = 24 + hours
            if(hours>23)
                hours = hours - 24
        }
        mins = m
        seconds = s
        hourListView.positionViewAtIndex(hours, ListView.Center)
        minListView.positionViewAtIndex(mins, ListView.Center)
        secondListView.positionViewAtIndex(seconds, ListView.Center)
    }

    function resetTime(){
        setTime(new Date().toLocaleString(Qt.locale(), "hh"),
                new Date().toLocaleString(Qt.locale(), "mm"),
                new Date().toLocaleString(Qt.locale(), "ss"))
    }


}
