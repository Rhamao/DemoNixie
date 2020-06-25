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
Column{
    property int redCode: 0
    property int greenCode: 0
    property int blueCode: 0
    property color rgbColor: Qt.rgba(redCode/255, greenCode/255, blueCode/255, 1)
    property int _height: 190
    id: rgbSliders
    spacing: 20
    anchors.verticalCenter: parent.verticalCenter
    rotation: 270
    DemoNixieSlider {
        width: _height
        from: 0
        value: 255/3
        to: 255
        backgroundColor: "red"
        onValueChanged: {
            redCode = value
            rgbColor = Qt.rgba(redCode/255, greenCode/255, blueCode/255, 1)
        }
        Component.onCompleted: {
            redCode = value
            rgbColor = Qt.rgba(redCode/255, greenCode/255, blueCode/255, 1)
        }
    }
    DemoNixieSlider {
        width: _height
        from: 0
        value: (255/3)*2
        to: 255
        backgroundColor: "green"
        onValueChanged: {
            greenCode = value
            rgbColor = Qt.rgba(redCode/255, greenCode/255, blueCode/255, 1)
        }
        Component.onCompleted: {
            greenCode = value
            rgbColor = Qt.rgba(redCode/255, greenCode/255, blueCode/255, 1)
        }
    }
    DemoNixieSlider {
        width: _height
        from: 0
        value: 255
        to: 255
        backgroundColor: "blue"
        onValueChanged: {
            blueCode = value
            rgbColor = Qt.rgba(redCode/255, greenCode/255, blueCode/255, 1)
        }
        Component.onCompleted: {
            blueCode = value
            rgbColor = Qt.rgba(redCode/255, greenCode/255, blueCode/255, 1)
        }
    }
}
