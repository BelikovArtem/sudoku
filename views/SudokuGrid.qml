import QtQuick
import QtQuick.Layouts
import QtQuick.Controls

Item {
    property int spacing: 10

    GridLayout {
        rows: 3
        rowSpacing: spacing
        columns: 3
        columnSpacing: spacing

        Rectangle {
            id: first
            Layout.fillHeight: true
            Layout.fillWidth: true


        }
    }
}
