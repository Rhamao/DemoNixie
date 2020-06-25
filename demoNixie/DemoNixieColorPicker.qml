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
Item{
    id:root
    property int redBuffer: 0
    property int greenBuffer: 0
    property int blueBuffer: 0
    property color colorPicked: Qt.rgba(redBuffer/255, greenBuffer/255, blueBuffer/255, 1)
    property bool highlightCircle: false
    property bool circleClicked: false
    width: highlighter.width + rgbSliders.width
    height: highlighter.height + rgbSliders.height
    Row{
        Rectangle{
            id: circle
            border.width: 5
            width: 190; height: width; radius: width;
            color: Qt.rgba(redBuffer/255, greenBuffer/255, blueBuffer/255, 1)
            Rectangle{
                id:highlighter
                anchors.centerIn: circle
                width:circle.width+10
                height: width
                radius: width
                color: "white"
                opacity: 0.125
                visible: highlightCircle
            }
            MouseArea{
                anchors.fill: parent
                onClicked: {
                    circleClicked = true
                    console.log("Color picker circle clicked : ", circleClicked)
                }
                onReleased: {
                    circleClicked = false
                    console.log("Color picker circle clicked : ", circleClicked)
                }
            }
        }

        RgbSliders {
            id: rgbSliders
        }
    }
}
