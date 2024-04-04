import QtQuick 2.15
import QtQuick.Controls

Button {
    id: button
    width: 100
    height: 200
    text: "Example"

    property int fontSize
    property string fontFamily
    property color backgroundColor: "black"
    property color textColor: "white"

    contentItem: Text {
        text: button.text

        font {
            family: fontFamily
            pixelSize: fontSize
            color: textColor
        }

        anchors.centerIn: parent
    }

    background: Rectangle {
        color: "backgroundColor"
        anchors.fill: parent
    }
}
