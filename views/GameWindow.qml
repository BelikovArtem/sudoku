import QtQuick
import QtQuick.Layouts
import QtQuick.Controls.Basic

Item {
    id: gameWindow
    visible: true

    SudokuGeniusLabel {
        id: sudokuGeniusLabel
    }

    Text {
        id: difficultyText

        anchors {
            top: parent.top
            topMargin: 20
            horizontalCenter: displayRow.horizontalCenter
        }

        text: "Difficulty: " + cViewModel.difficultyLevel
        color: "white"
        font.pixelSize: 32
        font.family: "Goudy Old Style"
    }

    RowLayout {
        id: displayRow

        spacing: 20

        anchors {
            margins: 30
            right: parent.right
            top: difficultyText.bottom
            left: sudokuGridFrame.right
        }

        Text {
            id: scoreText

            Layout.alignment: Text.AlignLeft

            text: "Score: " + cViewModel.score
            color: "white"
            font.pixelSize: 32
            font.family: "Goudy Old Style"
        }

        Text {
            id: mistakesText

            Layout.alignment: Text.AlignHCenter

            text: "Mistakes: " + cViewModel.mistakes + "/3"
            color: "white"
            font.pixelSize: 32
            font.family: "Goudy Old Style"
        }

        Text {
            id: timeText

            Layout.alignment: Text.AlignRight

            text: "Time: " + cViewModel.time
            color: "white"
            font.pixelSize: 32
            font.family: "Goudy Old Style"
        }
    }

    RowLayout {
        id: controlsRow

        spacing: 40

        anchors {
            margins: 30
            right: parent.right
            top: displayRow.bottom
            left: sudokuGridFrame.right

        }

        RoundButton {
            id: undoButton
            implicitWidth: 80
            implicitHeight: 80

            Layout.alignment: Qt.AlignLeft

            icon {
                width: parent.width
                height: parent.height
                color: "transparent"
                source: "images/undo.png"
            }
            flat: true

            onClicked: cViewModel.handleUndo()
        }

        RoundButton {
            id: eraseButton
            implicitWidth: 80
            implicitHeight: 80

            icon {
                width: parent.width
                height: parent.height
                color: "transparent"
                source: "images/erase.png"
            }
            flat: true

            onClicked: cViewModel.handleEraseCell()
        }

        RoundButton {
            id: noteButton
            implicitWidth: 80
            implicitHeight: 80

            icon {
                width: parent.width
                height: parent.height
                color: "transparent"
                source: "images/note.png"
            }
            flat: true

            onClicked: {
                cViewModel.isNoteMode = !cViewModel.isNoteMode
            }

        }

        RoundButton {
            id: tipButton
            implicitWidth: 80
            implicitHeight: 80

            Layout.alignment: Qt.AlignRight

            icon {
                width: parent.width
                height: parent.height
                color: "transparent"
                source: "images/tip.png"
            }
            flat: true

            onClicked: {

            }
        }
    }

    GridLayout {
        id: numbersGrid
        rows: 3
        columns: 3
        rowSpacing: 5
        columnSpacing: 5

        anchors {
            top: controlsRow.bottom
            topMargin: 30
            horizontalCenter: controlsRow.horizontalCenter
        }

        Repeater {
            model: 9

            CustomButton {
                implicitWidth: 100
                implicitHeight: 100

                property int buttonNumber: modelData + 1

                text: buttonNumber
                fontSize: 70
                fontFamily: "Copperplate Gothic Light"
                textColor: "#18228f"

                backgroundColor: "#6dcff6"

                onClicked: {
                    cViewModel.handleNumberEntered(buttonNumber)
                }
            }

        }
    }

    Frame {
        id: sudokuGridFrame
        padding: 6

        background: Rectangle {
            color: "transparent"
            border.color: "#1875f5"
            border.width: 5
        }

        anchors {
            top: sudokuGeniusLabel.bottom
            topMargin: 60
            left: parent.left
            leftMargin: 20
        }

        SudokuGrid {
            id: sudokuGrid
            anchors.fill: parent
        }
    }

    CustomButton {
        id: exitButton
        width: 250
        height: 50

        anchors {
            top: numbersGrid.bottom
            topMargin: 20
            right: numbersGrid.right
            rightMargin: 25
        }

        text: "Exit"
        textColor: "#18228f"
        fontSize: 40
        fontFamily: "Copperplate Gothic Light"
        backgroundColor: "#4f72eb"

        onClicked: {
            cViewModel.setGameState = "Loose"
            stackView.pop()
        }
    }

    Keys.onPressed: (event) => {
        switch (event.key) {
        /*
         * NUMBERS
         */
        case Qt.Key_1:
            cViewModel.handleNumberEntered(1)
            break;
        case Qt.Key_2:
            cViewModel.handleNumberEntered(2)
            break;
        case Qt.Key_3:
            cViewModel.handleNumberEntered(3)
            break;
        case Qt.Key_4:
            cViewModel.handleNumberEntered(4)
            break;
        case Qt.Key_5:
            cViewModel.handleNumberEntered(5)
            break;
        case Qt.Key_6:
            cViewModel.handleNumberEntered(6)
            break;
        case Qt.Key_7:
            cViewModel.handleNumberEntered(7)
            break;
        case Qt.Key_8:
            cViewModel.handleNumberEntered(8)
            break;
        case Qt.Key_9:
            cViewModel.handleNumberEntered(9)
            break;
        /*
         * ARROWS
         */
        case Qt.Key_Up:
            if (cViewModel.lastClickedCellIndex >= 9) {
                cViewModel.lastClickedCellIndex -= 9
            }
            break;
        case Qt.Key_Down:
            if (cViewModel.lastClickedCellIndex <= 71) {
                cViewModel.lastClickedCellIndex += 9
            }
            break;
        case Qt.Key_Left:
            if (cViewModel.lastClickedCellIndex > 0) {
                cViewModel.lastClickedCellIndex -= 1
            }
            break;
        case Qt.Key_Right:
            if (cViewModel.lastClickedCellIndex < 80) {
                cViewModel.lastClickedCellIndex += 1
            }
            break;
        }
    }

    Shortcut {
        sequence: "Ctrl+Z"
        onActivated: cViewModel.handleUndo()
    }
}
