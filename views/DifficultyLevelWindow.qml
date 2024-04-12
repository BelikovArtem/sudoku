import QtQuick
import QtQuick.Controls.Basic
import QtQuick.Layouts

Item {
    id: difficultyLvlWindow
    visible: true

    Text {
        id: selectDifficultyText

        anchors {
            topMargin: 100
            leftMargin: 50
            top: parent.top
            left: parent.left
        }

        text: "Select difficulty:"
        font.family: "Script MT Bold"
        color: "#1773ef"
        font.pixelSize: 80
    }

    ComboBox {
        id: comboBox
        height: 50
        anchors {
            margins: 50
            top: selectDifficultyText.bottom
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

    CustomButton {
        id: confirmButton
        width: 280
        height: 90

        anchors {
            //top: comboBox.top
            //topMargin: 200
            left: parent.left
            leftMargin: 200
            bottom: parent.bottom
            bottomMargin: 100
        }

        text: "Confirm"
        fontSize: 40
        fontFamily: "Copperplate Gothic Light"
        textColor: "#18228f"
        backgroundColor: "#4f72eb"

        onClicked: {
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
            sViewModel.getRandomGridFromServer(cViewModel.difficultyLevel)
        }
    }

    CustomButton {
        id: cancelButton
        width: 280
        height: 90

        anchors {
            //top: comboBox.top
            //topMargin: 200
            right: parent.right
            rightMargin: 200
            bottom: parent.bottom
            bottomMargin: 100
        }

        text: "Cancel"
        fontSize: 40
        fontFamily: "Copperplate Gothic Light"
        textColor: "#18228f"
        backgroundColor: "#4f72eb"

        onClicked: {
            stackView.pop()
        }
    }
}
