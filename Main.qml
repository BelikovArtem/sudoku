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
}
