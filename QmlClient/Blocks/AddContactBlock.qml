import QtQuick 1.1
import "../Controls"

Item {
    id: root

    property alias color: contentRectangle.color

    signal addContact(string jid)
    signal cancel();

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
                anchors {
                    fill: parent
                    margins: 5
                }

                Column {
                    spacing: 5
                    anchors.fill: parent

                    FormField {
                        id: contactJid

                        width: 390
                        height: 30
                        caption: "JID:"
                        captionWidth: 60
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
    }
}
