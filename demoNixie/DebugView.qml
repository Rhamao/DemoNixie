import QtQuick 2.0
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.11
import DbgLink 1.0



Item {
    id: element

    property var colorList: ["red", "green", "blue", "pink", "orange"]
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
            onClicked: dbg.clear()
        }

        Button {
            id: button1
            text: qsTr("testButton")
            onClicked: cpp.testButton()
        }

        Button {
            id: button2
            text: qsTr("ColorTest")
            property int colorIndex: 0
            onClicked: {
                dbg.appendColoredLine("You Only Look Once", colorList[colorIndex])
                colorIndex = colorIndex + 1
                if (colorIndex == colorList.length)
                    colorIndex = 0
            }
        }
    }

    Rectangle {
        id: rectangle
        color: "#ffffff"
        anchors.fill: textArea
    }

    TextArea {
        id: textArea
        anchors.top: rowLayout.bottom
        anchors.right: parent.right
        anchors.bottom: parent.bottom
        anchors.left: parent.left
        anchors.topMargin: 0
        textFormat: Text.AutoText
        placeholderText: qsTr("Text Area")
        text: dbg.text
        wrapMode: Text.WordWrap
    }


}

/*##^##
Designer {
    D{i:0;autoSize:true;height:480;width:640}D{i:1;anchors_width:640;anchors_x:0;anchors_y:0}
D{i:4;anchors_height:200;anchors_width:200}D{i:5;anchors_height:200;anchors_width:200}
D{i:6;anchors_x:0;anchors_y:94}
}
##^##*/
