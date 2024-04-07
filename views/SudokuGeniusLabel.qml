import QtQuick
import QtQuick.Controls.Basic

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
