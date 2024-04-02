import QtQuick
import QtQuick.Controls
import QtQuick.Layouts

Item {
    id: difficultyLvlWindow
    visible: true

    Label {
        id: selectDifficultyLabel
        width: 350
        height: 80
        anchors {
            topMargin: 100
            leftMargin: 50
            top: parent.top
            left: parent.left
        }

        Image {
            anchors.fill: parent
            source: "images/selectDifficulty.png"
        }
    }

    ComboBox {
        id: comboBox
        height: 50
        anchors {
            margins: 50
            top: selectDifficultyLabel.bottom
            left: parent.left
            right: parent.right
        }

        Component.onCompleted: currentIndex = 0

        model: ListModel {
            id: listModel
            ListElement { iconSource: "images/difficultyLow.png" }
            ListElement { iconSource: "images/difficultyMedium.png" }
            ListElement { iconSource: "images/difficultyHigh.png" }
        }

        delegate: ItemDelegate {
            id: dlg
            background: Image {
                width: 250
                height: 45
                source: iconSource
            }
        }

        contentItem: Image {
            id: contentItemImage
            fillMode: Image.PreserveAspectFit
            source: listModel.get(parent.currentIndex).iconSource
            horizontalAlignment: Image.AlignLeft
        }
    }

    Button {
        id: confirmButton
        width: 280
        height: 150

        anchors {
            top: comboBox.top
            topMargin: 300
            left: parent.left
            leftMargin: 200
            bottom: parent.bottom
            bottomMargin: 100
        }

        Text {
            text: "Confirm"
            font.pixelSize: 40
            font.family: "Copperplate Gothic Light"
            color: "#18228f"
            anchors.centerIn: parent
        }

        background: Rectangle {
            color: "#4f72eb"
        }

        onClicked: {
            // setDifficutyLevel
            switch (comboBox.currentIndex) {
            case 0:
                cViewModel.difficultyLevel = "Low"
                break;
            case 1:
                cViewModel.difficultyLevel = "Medium"
                break;
            case 2:
                cViewModel.difficultyLevel = "High"
                break;
            }

            // start new game
            cViewModel.startNewGame()
            stackView.push("GameWindow.qml")
        }
    }

    Button {
        id: cancelButton
        width: 280
        height: 150

        anchors {
            top: comboBox.top
            topMargin: 300
            right: parent.right
            rightMargin: 200
            bottom: parent.bottom
            bottomMargin: 100
        }

        Text {
            text: "Cancel"
            font.pixelSize: 40
            font.family: "Copperplate Gothic Light"
            color: "#18228f"
            anchors.centerIn: parent
        }

        background: Rectangle {
            color: "#4f72eb"
        }

        onClicked: {
            stackView.pop()
        }
    }
}
