import QtQuick 1.1
import "../Controls"

Rectangle {
    id: root

    signal addContact(string jid)
    signal cancel();

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

            Row {
                spacing: 10

                Text {
                    width: 80
                    height: 25
                    anchors.verticalCenter: parent.verticalCenter
                    font { family: "Arial"; pixelSize: 14 }
                    text: "JID:"
                }

                Rectangle {
                    width: 300
                    height: 25
                    TextEdit {
                        id: contactJid

                        anchors.fill: parent
                    }
                }
            }
            Row {
                spacing: 10
                anchors.horizontalCenter: parent.horizontalCenter

                Button {
                    text: "Add"
                    width: 100
                    height: 30
                    onClicked: {
                        root.addContact(contactJid.text);
                        contactJid.text = "";
                    }
                }
                Button {
                    text: "Cancel"
                    width: 100
                    height: 30
                    onClicked: {
                        root.cancel();
                    }
                }
            }
        }
    }
}
