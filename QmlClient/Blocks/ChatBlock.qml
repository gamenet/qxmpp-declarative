import QtQuick 1.1
import "../Models"
import "../Controls"

Rectangle {
    id: root

    property variant historyModel
    property bool active: false
    property string jid

    signal sendMessage(string jid, string message)
    signal cancel()

    border {
        color: "#000000"
        width: 2
    }
    color: "#EEEEEE"
    anchors.margins: 5
    height: 330

    Item {
        anchors.fill: parent
        anchors.margins: 5

        Column {
            spacing: 5

            anchors.fill: parent

            Row {
                spacing: 5

                Text {
                    text: "Send to: "
                    width: 80
                    style: Text.Normal
                    font { family: "Arial"; pixelSize: 14 }
                }

                Rectangle {
                    width: 300
                    height: 25

                    Text {
                        anchors.margins: 3
                        anchors.fill: parent
                        text: root.jid
                        font { family: "Arial"; pixelSize: 16 }
                    }

                }
            }
            Row {
                spacing: 5

                Text {
                    text: "History:"
                    width: 80
                    style: Text.Normal
                    font { family: "Arial"; pixelSize: 14 }
                }

                Rectangle {
                    width: 300
                    height: 125

                    color: "#BBBBBB"

                    ChatHistoryView {
                        id: historyView

                        model: historyModel.model
                        anchors.fill: parent
                    }
                }
            }

            Row {
                spacing: 5

                Text {
                    text: "Message:"
                    width: 80
                    style: Text.Normal
                    font { family: "Arial"; pixelSize: 14 }
                }

                Rectangle {
                    width: 300
                    height: 125

                    TextInput {
                        id: messageText

                        anchors.fill: parent
                        font { family: "Arial"; pixelSize: 16 }
                    }
                }
            }

            Row {
                spacing: 5

                Item {
                    width: 80
                    height: 1
                }

                Button {
                    id: sendButton

                    width: 100
                    height: 30
                    text: "Send"
                    onClicked: {
                        root.sendMessage(root.jid, messageText.text);
                        messageText.text = "";
                    }
                }

                Button {
                    id: cancelButton

                    width: 100
                    height: 30
                    text: "Cancel"
                    onClicked: {
                        root.cancel();
                        messageText.text = "";
                    }
                }
            }
        }
    }
}
