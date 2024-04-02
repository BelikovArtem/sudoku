import QtQuick
import QtQuick.Layouts
import QtQuick.Controls

Item {
    id: gameWindow
    visible: true

    Label {
        id: sudokuGenuisLabel
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

            Button {
                implicitWidth: 100
                implicitHeight: 100

                Text {
                    text: modelData
                    font.pixelSize: 70
                    font.family: "Copperplate Gothic Light"
                    color: "#18228f"
                    anchors.centerIn: parent
                }

                background: Rectangle {
                    color: "#6dcff6"
                }
            }

        }
    }


    // grid 1-9
    // SudokuGrid {

    // }

}
