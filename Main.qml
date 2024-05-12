import QtQuick
import QtQuick.Controls
import "views"

Window {
    id: rootWindow
    width: 1024
    height: 680
    visible: true
    title: "SudokuGenius"

    minimumWidth: 1000
    minimumHeight: 680

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

    Connections {
        target: cViewModel

        function onViewMessage(message) {
            warningPopup.warningText = message
            warningPopup.open()
        }

        function onScoreChanged() {
            if (cViewModel.gameState === "Win") {
                sViewModel.userScore = sViewModel.userScore + cViewModel.score
            }
        }
    }

    CustomPopup {
        id: warningPopup
        x: parent.width - width - 20
        y: parent.height - height - 20
        width: 550
        height: 50
    }


    property bool closing: false

    onClosing: {
        close.accepted = closing
        onTriggered: stackView.push("views/ExitWindow.qml")
    }

}
