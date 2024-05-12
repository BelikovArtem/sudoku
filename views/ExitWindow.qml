import QtQuick
import QtQuick.Controls

Window {
    id: exitWindow
    width: 456
    height: 156
    visible: true
    title: "Confirm exit"
    flags: Qt.Window | Qt.FramelessWindowHint | Qt.MSWindowsFixedSizeDialogHint

    Image {
       anchors.fill: parent
       source: "images/background.png"
    }

    Text {
        anchors {
            topMargin: 10
            horizontalCenter: parent.horizontalCenter
        }

        text: "Do you really want to exit?"
        font.family: "Script MT Bold"
        color: "#1773ef"
        font.pixelSize: 30
    }

    CustomButton {
        id: confirmButton
        width: 200
        height: 50

        anchors {
            left: parent.left
            leftMargin: 10
            bottom: parent.bottom
            bottomMargin: 10
        }

        text: "Confirm"
        fontSize: 20
        fontFamily: "Copperplate Gothic Light"
        textColor: "#18228f"
        backgroundColor: "#4f72eb"

        onClicked: {
            Qt.exit(0)
        }
    }

    CustomButton {
        id: cancelButton
        width: 200
        height: 50

        anchors {
            right: parent.right
            rightMargin: 10
            bottom: parent.bottom
            bottomMargin: 10
        }

        text: "Cancel"
        fontSize: 20
        fontFamily: "Copperplate Gothic Light"
        textColor: "#18228f"
        backgroundColor: "#4f72eb"

        onClicked: {
            exitWindow.close()
        }
    }
}
