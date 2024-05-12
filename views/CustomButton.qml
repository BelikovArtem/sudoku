import QtQuick
import QtQuick.Controls.Basic

Button {
    width: 100
    height: 100
    visible: true

    text: " "
    property int fontSize: 26
    property color textColor: "white"
    property string fontFamily: "Arial"
    property color backgroundColor: "black"
    property int horAl: 4       // Text.AlignHCenter
    property int vertAl: 128    // Text.AlignVCenter

    contentItem: Text {
        text: parent.text

        font {
            pixelSize: fontSize
            family: fontFamily
        }

        color: textColor

        horizontalAlignment: horAl
        verticalAlignment: vertAl
    }

    background: Rectangle {
        color: backgroundColor
    }
}
