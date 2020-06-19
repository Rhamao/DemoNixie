import QtQuick 2.12
import QtQuick.Controls 2.12
import QtQuick.Layouts 1.12
import DbgLink 1.0
import BleLink 1.0


Item {
    id: element

    property var colorList: ["red", "green", "blue", "pink", "orange"]

    BleLink {
        id:ble
        Component.onCompleted: cpp.handleQmlBleInit(ble);

    }
    DbgLink {
        id:dbg
        Component.onCompleted: cpp.handleQmlDbgInit(dbg);
    }



    RowLayout {
        id: rowLayout
        height: 80
        anchors.top: parent.top
        anchors.topMargin: 0
        anchors.left: parent.left
        anchors.leftMargin: 0
        anchors.right: parent.right
        anchors.rightMargin: 0

        Button {
            id: button
            text: qsTr("clear")
            Layout.fillWidth: true
            onClicked: dbg.clear()
        }

        Button {
            id: button1
            text: qsTr("Connect")
            Layout.fillWidth: true
            onClicked: ble.runDiscovery()
        }

        Button {
            id: button2
            text: qsTr("write Time")
            Layout.fillWidth: true
            property int colorIndex: 0
            onClicked: {
                ble.writeTime(10,42,20)
            }
        }
        Button {
            id: button3
            text: qsTr("write Animation")
            Layout.fillWidth: true
            property int colorIndex: 0
            onClicked: {
                ble.writeAnimation(false,"red", 42, rectangle.color, 142, "purple", 0)
            }
        }
    }

    Rectangle {
        id: rectangle
//        color:
        color: (ble.connected) ? "#FEEDED" : "#ffffff"
        anchors.fill: flickableText
    }

    Flickable{
        id:flickableText
        anchors.top: rowLayout.bottom
        anchors.right: parent.right
        anchors.bottom: parent.bottom
        anchors.left: parent.left
        anchors.topMargin: 0
        TextArea.flickable: TextArea {
            id: textArea
            readOnly: true
            selectByMouse: false

            textFormat: Text.AutoText
            placeholderText: qsTr("Text Area")
            text: dbg.text
            wrapMode: Text.WordWrap
        }
        ScrollBar.vertical: ScrollBar { }
    }

}

/*##^##
Designer {
    D{i:0;autoSize:true;height:480;width:640}D{i:1;anchors_width:640;anchors_x:0;anchors_y:0}
D{i:4;anchors_height:200;anchors_width:200}D{i:5;anchors_height:200;anchors_width:200}
D{i:6;anchors_x:0;anchors_y:94}
}
##^##*/
