import QtQuick
import QtQuick.Controls.Basic
import QtQuick.Layouts

Item {

    id: loginWindow
    visible: true

    Label {
        id: sudokuGeniusLabel
        width: 300
        height: 70
        anchors.margins: 20
        anchors.top: parent.top
        anchors.left: parent.left

        Text {
            id: sudokuText
            text: "Sudoku"
            font.family: "Eras Bold ITC"
            color: "#2d3bbb"
            font.pixelSize: 46
        }

        Text {
            anchors.left: sudokuText.right
            text: "Genius"
            font.family: "Script MT Bold"
            color: "#1773ef"
            font.pixelSize: 46
        }
    }

    Rectangle {
        id: usernameRect
        color: "white"

        width: 650
        height: 60

        anchors {
            top: sudokuGeniusLabel.bottom
            topMargin: 90
            horizontalCenter: parent.horizontalCenter
        }

        TextInput {
            id: usernameInput
            text: "Username"
            anchors.fill: parent
            maximumLength: 20

            font {
                pixelSize: 30
                family: "Copperplate Gothic Light"
            }

            horizontalAlignment: Text.AlignLeft
            verticalAlignment: Text.AlignVCenter

            color: "#8d90ae"
        }
    }

    Rectangle {
        id: passwordRect
        color: "white"

        width: 650
        height: 60

        anchors {
            top: usernameRect.bottom
            topMargin: 50
            horizontalCenter: parent.horizontalCenter
        }

        TextInput {
            id: passwordInput
            text: "Password"
            anchors.fill: parent
            maximumLength: 20

            echoMode: TextInput.Password

            font {
                pixelSize: 30
                family: "Copperplate Gothic Light"
            }

            horizontalAlignment: Text.AlignLeft
            verticalAlignment: Text.AlignVCenter

            color: "#8d90ae"
        }
    }

    RowLayout {
        anchors {
            top: passwordRect.bottom
            topMargin: 100
            bottom: parent.bottom
            bottomMargin: 150
            left: parent.left
            leftMargin: 100
            right: parent.right
            rightMargin: 100
        }

        spacing: 100

        CustomButton {
            id: signUpButton
            width: 250
            height: 50

            Layout.fillWidth: true
            Layout.fillHeight: true

            text: "Sign Up"
            textColor: "#18228f"
            fontSize: 40
            fontFamily: "Copperplate Gothic Light"
            backgroundColor: "#4f72eb"

            onClicked: {
                sViewModel.signUp(usernameInput.text, passwordInput.text)
            }
        }

        CustomButton {
            id: logInButton
            width: 250
            height: 50

            Layout.fillWidth: true
            Layout.fillHeight: true

            text: "Log In"
            textColor: "#18228f"
            fontSize: 40
            fontFamily: "Copperplate Gothic Light"
            backgroundColor: "#4f72eb"

            onClicked: {
                sViewModel.logIn(usernameInput.text, passwordInput.text)
            }
        }
    }

}
