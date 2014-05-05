import QtQuick 1.1
import "../Controls" as Controls

Item {
    id: root

    property string jid
    property alias color: contentRectangle.color
    signal accepted()
    signal refused()

    Rectangle {
        anchors.fill: parent
        color: "#000000"

        Rectangle {
            id: contentRectangle

            color: "#EEEEEE"
            anchors {
                fill: parent
                margins: 1
            }

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
    }
}
