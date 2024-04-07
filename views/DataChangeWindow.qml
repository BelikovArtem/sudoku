import QtQuick
import QtQuick.Controls.Basic
import QtQuick.Layouts

Item {
    id: dataChangeWindow
    visible: true

    SudokuGeniusLabel {
        id: sudokuGeniusLabel
    }

    Text {
        id: changeDataLabel
        anchors {
            top: sudokuGeniusLabel.bottom
            topMargin: 20
            horizontalCenter: parent.horizontalCenter
        }

        text: "Change Data"
        font.family: "Script MT Bold"
        color: "#1773ef"
        font.pixelSize: 46
    }

    ColumnLayout {
        anchors {
            top: changeDataLabel.bottom
            topMargin: 50
            left: parent.left
            leftMargin: 50
            right: parent.right
            rightMargin: 50
        }

        spacing: 25

        Rectangle {
            id: usernameRect
            color: "white"

            width: 650
            height: 60

            Layout.fillWidth: true
            Layout.fillHeight: true

            TextInput {
                id: usernameInput
                text: sViewModel.userName
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

        CustomButton {
            id: changeUsernameButton

            Layout.fillWidth: true
            Layout.fillHeight: true

            text: "Change Username"
            textColor: "#18228f"
            fontSize: 40
            fontFamily: "Copperplate Gothic Light"
            backgroundColor: "#4f72eb"

            onClicked: {
                sViewModel.userName = usernameInput.text
            }
        }

        Rectangle {
            id: passwordRect
            color: "white"

            Layout.fillWidth: true
            Layout.fillHeight: true

            width: 650
            height: 60

            TextInput {
                id: passwordInput
                text: sViewModel.userPassword
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

        CustomButton {
            id: changePasswordButton

            Layout.fillWidth: true
            Layout.fillHeight: true

            text: "Change Password"
            textColor: "#18228f"
            fontSize: 40
            fontFamily: "Copperplate Gothic Light"
            backgroundColor: "#4f72eb"

            onClicked: {
                sViewModel.userPassword = passwordInput.text
            }
        }

        CustomButton {
            id: exitButton
            width: 250
            height: 50

            Layout.fillWidth: true
            Layout.fillHeight: true

            text: "Exit"
            textColor: "#18228f"
            fontSize: 40
            fontFamily: "Copperplate Gothic Light"
            backgroundColor: "#4f72eb"

            onClicked: {
                stackView.pop()
            }
        }
    }
}
