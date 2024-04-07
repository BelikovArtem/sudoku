import QtQuick
import QtQuick.Controls.Basic

Popup {
    modal: false

    property string warningText: "Example"

    background: Rectangle {
        color: "#d7f4ff"
    }

    Text {
        text: warningPopup.warningText

        font {
            pixelSize: 26
            family: "Copperplate Gothic Light"
        }

        color: "#18228f"

        anchors.centerIn: parent
    }
}
