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

                    property int gridOffset: parentRep.calculateGridOffset(gridIndex)
                    property int cellIndexInGrid: parentRep.calculateCellIndex(modelData)
                    property int index: cellIndexInGrid + gridOffset

                    text: cViewModel.grid[index]
                    fontSize: 40
                    fontFamily: "Copperplate Gothic Light"
                    textColor: "#18228f"
                    backgroundColor: "white"

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

        function onLastClickedCellIndexChanged() {
            const sudokuSquares = sudokuGrid.children
            let lastClickedCellIndex = cViewModel.lastClickedCellIndex

            for (let j = 0; j < 9; j++) {
                const squareCells = sudokuSquares[j].children

                // the lastClickedCellIndex lies in the square?
                let isInSquare = contains(squareCells, lastClickedCellIndex)


                for (let i = 0; i < 9; i++) {
                    let cell = squareCells[i]
                    let index = cell.index

                    let rowIndex = Math.floor(index / 9)

                    //cell === clickedCell
                    if (index === lastClickedCellIndex) {
                        cell.backgroundColor = "#bbdefb"
                        continue
                    }
                    // cell.number === clickedCell.number
                    if (cViewModel.grid[index] === cViewModel.grid[lastClickedCellIndex] &&
                            cViewModel.grid[index] !== " ") {
                        cell.backgroundColor = "#c3d7ea"
                        continue
                    }
                    // cell is in a square with the clicked cell
                    if (isInSquare) {
                        cell.backgroundColor = "#e2ebf3"
                        continue
                    }
                    // cell is in a row with the clicked cell
                    if ((lastClickedCellIndex >= rowIndex * 9 &&
                        lastClickedCellIndex <= rowIndex * 9 + 8) &&
                        (index >= rowIndex * 9 &&
                        index <= rowIndex * 9 + 8)) {
                        cell.backgroundColor = "#e2ebf3"
                        continue
                    }
                    // cell is in a column with the clicked cell
                    if ((Math.max(lastClickedCellIndex, index) -
                        Math.min(lastClickedCellIndex, index)) % 9 === 0) {
                        cell.backgroundColor = "#e2ebf3"
                        continue
                    }

                    cell.backgroundColor = "white"
                }
            }
        }

        function contains(array, value) {
            for (let i = 0; i < array.length; i++) {
                if (array[i].index === value)
                    return true
            }
            return false
        }
    }
}
