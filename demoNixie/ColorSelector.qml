import QtQuick 2.14
import QtQuick.Window 2.14
import QtQuick.Controls 2.14


//Home page


Button{
    id:root
    property color _color: "red"
    property int size: 45
    Rectangle{
        width : size
        height: size
        radius: size
        color : !root.down ? _color : Qt.lighter(_color)
    }
}

