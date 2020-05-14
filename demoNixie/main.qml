import QtQuick 2.14
import QtQuick.Window 2.14

Item {

    width: 640
    height: 480

    Text {
        id: helloText
        text: "Hello world!"
        y: 30
        anchors.horizontalCenter: page.horizontalCenter
        font.pointSize: 24; font.bold: true

        }

}
