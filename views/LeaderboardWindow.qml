import QtQuick
import QtQuick.Controls.Basic
import QtQuick.Layouts

Item {
    id: leaderboardWindow
    visible: true

    SudokuGeniusLabel {
        id: sudokuGeniusLabel
    }

    CustomButton {
        id: exitButton
        width: 250
        height: 50

        anchors {
            margins: 25
            top: parent.top
            right: parent.right
        }

        text: "Exit"
        textColor: "#18228f"
        fontSize: 35
        fontFamily: "Copperplate Gothic Light"
        backgroundColor: "#4f72eb"

        onClicked: {
            stackView.pop()
        }
    }

    Text {
        id: leaderboardLabel
        anchors {
            top: sudokuGeniusLabel.bottom
            topMargin: 10
            horizontalCenter: parent.horizontalCenter
        }

        text: "Leaderboard"
        font.family: "Script MT Bold"
        color: "#1773ef"
        font.pixelSize: 46
    }

    ListModel {
        id: leadersModel
    }

    ListView {
        id: leadersView
        model: leadersModel

        anchors {
            top: leaderboardLabel.bottom
            topMargin: 80
            left: parent.left
            leftMargin: 50
            right: parent.right
            rightMargin: 50
            bottom: parent.bottom
            bottomMargin: 50
        }

        spacing: 5

        delegate: Rectangle {
            width: leadersView.width
            height: 100

            color: "#d7f4ff"
            radius: 10

            Label {
                anchors {
                    left: parent.left
                    leftMargin: 20
                    verticalCenter: parent.verticalCenter
                }

                width: 70
                height: 70

                Image {
                    anchors.fill: parent
                    source: "images/profile.png"
                }
            }

            Text {
                anchors {
                    left: parent.left
                    leftMargin: 150
                    verticalCenter: parent.verticalCenter
                }

                text: model.user_name.length >= 10 ? reduceString(model.user_name, 7) : model.user_name
                color: "#1773ef"

                font {
                    family: "Copperplate Gothic Light"
                    pixelSize: 40
                }
            }

            Text {
                anchors {
                    left: parent.left
                    leftMargin: 500
                    verticalCenter: parent.verticalCenter
                }

                text: "Score: " + model.user_score
                color: "#1773ef"

                font {
                    family: "Copperplate Gothic Light"
                    pixelSize: 40
                }
            }
        }

        Component.onCompleted: sViewModel.getLeaderboard(15)
    }

    Connections {
        target: sViewModel

        function onLeaderboardRecievedFromServer(users) {
            for (let i = 0; i < users.length; i++) {
                leadersModel.append({
                    "user_name": users[i].user_name,
                    "user_score": users[i].user_score
                })
            }
        }
    }

    function reduceString(str, maximumSymbols) {
        let reducedStr = ""
        for (let i = 0; i < maximumSymbols; i++) {
            reducedStr += str.charAt(i)
        }
        return reducedStr + "..."
    }

}
