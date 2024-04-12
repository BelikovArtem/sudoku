import QtQuick
import QtQuick.Layouts
import QtQuick.Controls

GridLayout {
    id: sudokuGrid
    rows: 3
    columns: 3
    rowSpacing: 5
    columnSpacing: 5

    property int lastEnteredNumber: -1

    Repeater {
        id: parentRep
        model: 9

        function calculateGridOffset(gridIndex) {
            if (gridIndex < 3)
                return gridIndex * 3
            else if (gridIndex >= 3 && gridIndex < 6) {
                gridIndex %= 3
                return 27 + gridIndex * 3
            } else {
                gridIndex %= 6
                return 54 + gridIndex * 3
            }
        }

        function calculateCellIndex(cellIndex) {
            if (cellIndex < 3)
                return cellIndex
            else if (cellIndex >= 3 && cellIndex < 6)
                return cellIndex += 6
            else
                return cellIndex += 12
        }

        function getCellColor(cellIndex, gridIndex, cellIndexInGrid) {
            if (cellIndex === cViewModel.lastClickedCellIndex)
                return "#bbdefb"
            else if (cViewModel.grid[cellIndex] === cViewModel.grid[cViewModel.lastClickedCellIndex] &&
                     cViewModel.grid[cellIndex] !== " ")
                return "#c3d7ea"
            else
                return "white"
        }

        GridLayout {
            id: sudokuSquareGrid
            rows: 3
            columns: 3
            rowSpacing: 1
            columnSpacing: 1

            property int gridIndex: modelData
            Repeater {
                id: childRep
                model: 9

                CustomButton {
                    implicitWidth: 50
                    implicitHeight: 50

                    property int index: parentRep.calculateCellIndex(modelData) + parentRep.calculateGridOffset(gridIndex)

                    text: cViewModel.grid[index]
                    fontSize: 40
                    fontFamily: "Copperplate Gothic Light"
                    textColor: "#18228f"
                    backgroundColor: parentRep.getCellColor(index, gridIndex, modelData)

                    onClicked: {
                        cViewModel.handleCellClicked(index)
                    }
                }
            }
        }
    }

    Connections {
        target: cViewModel

        function onMistakesChanged() {
            const sudokuSquares = sudokuGrid.children

            for (let j = 0; j < 9; j++) {
                const gridCells = sudokuSquares[j].children
                for (let i = 0; i < 9; i++) {
                    let cell = gridCells[i]
                    if (cell.index === cViewModel.lastClickedCellIndex) {
                        cell.textColor = "red"
                        cell.text = lastEnteredNumber
                        return
                    }
                }
            }
        }

        function onGridChanged() {
            const sudokuSquares = sudokuGrid.children

            for (let j = 0; j < 9; j++) {
                const gridCells = sudokuSquares[j].children
                for (let i = 0; i < 9; i++) {
                    let cell = gridCells[i]
                    if (cell.index === cViewModel.lastClickedCellIndex) {
                        cell.textColor = "#18228f"
                        cell.text = cViewModel.grid[cell.index]
                        return
                    }
                }
            }
        }
    }
}
