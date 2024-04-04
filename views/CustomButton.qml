import QtQuick
import QtQuick.Controls.Basic

Button {
    width: 100
    height: 100
    visible: true

    text: "Example"
    property int fontSize: 26
    property color textColor: "white"
    property string fontFamily: "Arial"
    property color backgroundColor: "black"

    contentItem: Text {
        text: parent.text

        font {
            pixelSize: fontSize
            family: fontFamily
        }

        color: textColor

        horizontalAlignment : Text.AlignHCenter
        verticalAlignment : Text.AlignVCenter
    }

    background: Rectangle {
        color: backgroundColor
    }
}
