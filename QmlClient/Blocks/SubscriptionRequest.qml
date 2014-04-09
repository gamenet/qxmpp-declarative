import QtQuick 1.1
import "../Controls" as Controls

Rectangle {
    id: root

    property string jid
    signal accepted()
    signal refused()

    border {
        color: "#000000"
        width: 2
    }
    color: "#EEEEEE"
    anchors.margins: 5

    Item {
        anchors.fill: parent
        anchors.margins: 5

        Column {
            spacing: 5
            anchors.fill: parent

            Text {
                id: contactJid

                width: 200
                height: 30
                text: "Subscription request from: " + jid
                font {
                    family: "Arial"
                    pixelSize: 14
                }
            }

            Row {
                spacing: 10
                anchors.horizontalCenter: parent.horizontalCenter

                Controls.Button {
                    text: "Accept"
                    width: 60
                    height: 25
                    onClicked: root.accepted();
                }
                Controls.Button {
                    text: "Refuse"
                    width: 60
                    height: 25
                    onClicked: root.refused();
                }
            }
        }
    }
}
