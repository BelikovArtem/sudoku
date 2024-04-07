import QtQuick
import QtQuick.Layouts
import QtQuick.Controls.Basic

Item {
    id: gameWindow
    visible: true

    SudokuGeniusLabel {
        id: sudokuGeniusLabel
    }

    Label {
        id: difficultyLabel

        width: 100
        height: 50

        anchors {
            top: parent.top
            topMargin: 20
            right: parent.right
            rightMargin: 300
        }

        Text {
            text: "Difficulty: " + cViewModel.difficultyLevel
            color: "white"
            font.pixelSize: 36
            font.family: "Goudy Old Style"
        }
    }

    Label {
        id: scoreLabel

        width: 70
        height: 30

        anchors {
            top: difficultyLabel.bottom
            topMargin: 30
            right: parent.right
            rightMargin: 450
        }

        Text {
            text: "Score: " + cViewModel.score
            color: "white"
            font.pixelSize: 36
            font.family: "Goudy Old Style"
        }
    }

    Label {
        id: mistakesLabel

        width: 70
        height: 30

        anchors {
            top: difficultyLabel.bottom
            topMargin: 30
            left: scoreLabel.right
            leftMargin: 70
        }

        Text {
            text: "Mistakes: " + cViewModel.mistakes + "/3"
            color: "white"
            font.pixelSize: 36
            font.family: "Goudy Old Style"
        }
    }

    Label {
        id: timeLabel

        width: 70
        height: 30

        anchors {
            top: difficultyLabel.bottom
            topMargin: 30
            left: mistakesLabel.right
            leftMargin: 150
        }

        Text {
            text: "Time: " + cViewModel.time
            color: "white"
            font.pixelSize: 36
            font.family: "Goudy Old Style"
        }
    }

    GridLayout {
        id: numbersGrid
        rows: 3
        columns: 3
        rowSpacing: 5
        columnSpacing: 5

        anchors {
            top: timeLabel.bottom
            topMargin: 150
            right: parent.right
            rightMargin: 80
        }

        Repeater {
            model: [1, 2, 3, 4, 5, 6, 7, 8, 9]

            CustomButton {
                implicitWidth: 100
                implicitHeight: 100

                text: modelData
                fontSize: 70
                fontFamily: "Copperplate Gothic Light"
                textColor: "#18228f"

                backgroundColor: "#6dcff6"
            }

        }
    }

    Frame {
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
            anchors.fill: parent
        }
    }

}
