import QtQuick
import QtQuick.Layouts
import QtQuick.Controls

GridLayout {
    id: sudokuGrid
    rows: 3
    columns: 3
    rowSpacing: 5
    columnSpacing: 5

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
                    backgroundColor: "white"
                }
            }
        }
    }
}
