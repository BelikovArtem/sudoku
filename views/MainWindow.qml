import QtQuick
import QtQuick.Controls

Item {
    id: mainWindow
    visible: true

    SudokuGeniusLabel {
        id: sudokuGeniusLabel
    }

    RoundButton {
        id: profileButton
        width: 90
        height: 90
        radius: 35

        anchors.margins: 10
        anchors.top: parent.top
        anchors.right: settingsButton.left

        icon.width: parent.width
        icon.height: parent.height
        icon.source: "images/profile.png"
        flat: true

        onClicked: {
            if (sViewModel.isConnected) {
                stackView.push("LoginWindow.qml")
            } else {
                warningPopup.warningText = "Server isn`t connected"
                warningPopup.open()
            }
        }
    }

    RoundButton {
        id: settingsButton
        width: 90
        height: 90
        radius: 35

        anchors.margins: 10
        anchors.top: parent.top
        anchors.right: parent.right

        icon.width: parent.width
        icon.height: parent.height
        icon.source: "images/settings.png"
        flat: true

        onClicked: {
            stackView.push("SettingsWindow.qml");
        }
    }

    Label {
        id: sudokuIcon
        width: 550
        height: 550

        anchors {
            left: parent.left
            leftMargin: 40
            bottom: parent.bottom
            bottomMargin: 25
            top: sudokuGeniusLabel.bottom
            topMargin: 80
        }

        Image {
            anchors.fill: parent
            source: "images/sudokuIcon.png"
        }
    }

    CustomButton {
        id: newGameButton
        width: 300
        height: 90

        anchors {
            top: settingsButton.bottom
            topMargin: 80
            right: parent.right
            rightMargin: 50
        }

        text: "New Game"
        textColor: "#18228f"
        fontSize: 40
        fontFamily: "Copperplate Gothic Light"
        backgroundColor: "#4f72eb"

        onClicked: {
            stackView.push("DifficultyLevelWindow.qml")
        }
    }

    CustomButton {
        id: leaderboardButton
        width: 300
        height: 90

        anchors {
            top: newGameButton.bottom
            topMargin: 60
            right: parent.right
            rightMargin: 50
        }

        text: "Leaderboard"
        textColor: "#18228f"
        fontSize: 40
        fontFamily: "Copperplate Gothic Light"
        backgroundColor: "#4f72eb"

        onClicked: {
            if (sViewModel.isConnected) {
                stackView.push("LeaderboardWindow.qml")
            } else {
                warningPopup.warningText = "Server isn`t connected"
                warningPopup.open()
            }
        }

    }

    CustomButton {
        id: exitButton
        width: 300
        height: 90

        anchors {
            top: leaderboardButton.bottom
            topMargin: 60
            right: parent.right
            rightMargin: 50
        }

        text: "Exit"
        textColor: "#18228f"
        fontSize: 40
        fontFamily: "Copperplate Gothic Light"
        backgroundColor: "#4f72eb"

    }

    CustomPopup {
        id: warningPopup
        x: parent.width - width - 20
        y: parent.height - height - 20
        width: 550
        height: 50
    }
}
