import QtQuick
import QtQuick.Layouts
import QtQuick.Controls.Basic

Button {
    id: gameCell
    width: 100
    height: 100
    visible: true

    property string textVal: "Example"
    property color textColor: "white"
    property string fontFamily: "Arial"
    property color backgroundColor: "black"
    padding: 5

    function fillGridData() {
        let gridData = [" ", " ", " ",
                        " ", " ", " ",
                        " ", " ", " "]

        if (textVal.length < 9) return gridData

        let cnt = 0
        for (let i = 0; i < textVal.length; i++) {
            if (i % 2 == 0) {
                gridData[cnt] = textVal[i]
                cnt++
            }
        }
        return gridData
    }

    GridLayout {
        id: noteModeGrid
        rows: 3
        columns: 3

        rowSpacing: 0
        columnSpacing: 0

        anchors.verticalCenter: parent.verticalCenter
        anchors.horizontalCenter: parent.horizontalCenter

        Repeater {
            model: fillGridData()

            Rectangle {
                width: 15
                height: 15
                color: "transparent"

                Text {
                    text: modelData

                    font {
                        pixelSize: 15
                        family: fontFamily
                    }

                    color: textColor

                    anchors {
                        verticalCenter: parent.verticalCenter
                        horizontalCenter: parent.horizontalCenter
                    }
                }
            }
        }
    }

    background: Rectangle {
        color: backgroundColor

        Text {
            text: gameCell.textVal.length < 9 ? gameCell.textVal : " "

            font {
                pixelSize: 40
                family: fontFamily
            }

            color: textColor

            anchors {
                verticalCenter: parent.verticalCenter
                horizontalCenter: parent.horizontalCenter
            }
        }
    }
}
