import QtQuick
import QtQuick.Controls
import "views"

Window {
    width: 1024
    height: 680
    visible: true
    title: "SudokuGenius"

    StackView {
        id: stackView

        anchors.fill: parent

        Image {
           anchors.fill: parent
           source: "views/images/background.png"
        }

        initialItem: "views/MainWindow.qml"
    }

    Connections {
        target: sViewModel

        function onViewMessage(message) {
            warningPopup.warningText = message
            warningPopup.open()
        }

        function onGridFromServer(grid) {
            cViewModel.startNewGame(grid)
            stackView.push("views/GameWindow.qml")
        }
    }

    CustomPopup {
        id: warningPopup
        x: parent.width - width - 20
        y: parent.height - height - 20
        width: 550
        height: 50
    }
}
