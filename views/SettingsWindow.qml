import QtQuick
import QtQuick.Controls.Basic

Item {
    id: settingsWindow
    visible: true

    SudokuGeniusLabel {
        id: sudokuGeniusLabel
    }

    Text {
        id: settingsLabel
        anchors {
            top: sudokuGeniusLabel.bottom
            topMargin: 20
            horizontalCenter: parent.horizontalCenter
        }

        text: "Settings"
        font.family: "Script MT Bold"
        color: "#1773ef"
        font.pixelSize: 46
    }

    CustomButton {
        id: changeProfileButton
        width: 300
        height: 90

        anchors {
            top: settingsLabel.bottom
            topMargin: 50
            horizontalCenter: parent.horizontalCenter
        }

        text: "Change Profile"
        textColor: "#18228f"
        fontSize: 35
        fontFamily: "Copperplate Gothic Light"
        backgroundColor: "#4f72eb"

        onClicked: {
            if (sViewModel.isConnected) {
                stackView.push("LoginWindow.qml")
            } else {
                warningPopup.warningText = "Please, Log In or Sign Up"
                warningPopup.open()
            }
        }
    }

    CustomButton {
        id: changeDataButton
        width: 300
        height: 90

        anchors {
            top: changeProfileButton.bottom
            topMargin: 50
            horizontalCenter: parent.horizontalCenter
        }

        text: "Change Data"
        textColor: "#18228f"
        fontSize: 35
        fontFamily: "Copperplate Gothic Light"
        backgroundColor: "#4f72eb"

        onClicked: {
            if (sViewModel.isConnected && sViewModel.isAuthorized) {
                stackView.push("DataChangeWindow.qml")
            } else {
                warningPopup.warningText = "Please, Log In or Sign Up"
                warningPopup.open()
            }
        }
    }

    CustomButton {
        id: exitButton
        width: 300
        height: 90

        anchors {
            top: changeDataButton.bottom
            topMargin: 50
            horizontalCenter: parent.horizontalCenter
        }

        text: "Exit"
        textColor: "#18228f"
        fontSize: 35
        fontFamily: "Copperplate Gothic Light"
        backgroundColor: "#4f72eb"

        onClicked: {
            stackView.pop()
        }
    }

    CustomPopup {
        id: warningPopup
        x: parent.width - width - 20
        y: parent.height - height - 20
        width: 550
        height: 50
    }
}
