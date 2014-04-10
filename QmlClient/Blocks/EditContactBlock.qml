import QtQuick 1.1
import QXmpp 1.0
import "../Models"
import "../Controls"

Rectangle {
    id: root

    property variant rosterManager
    property string jid

    signal apply()
    signal cancel()

    onJidChanged: {
        if (jid == "") {
            return;
        }

        var nickName = rosterManager.getNickname(jid);
        nicknameField.text = nickName;

        var subType = rosterManager.getSubscription(jid);
        subField.text = d.subscriptionToString(rosterManager.getSubscription(jid));
        groupsField.text = rosterManager.getGroups(jid).join(";");
    }

    QtObject {
        id: d

        function subscriptionToString(sub) {
            if (sub == QXmppRosterManager.None) {
                return "None";
            } else if (sub == QXmppRosterManager.From) {
                return "From";
            } else if (sub == QXmppRosterManager.To) {
                return "To";
            } else if (sub == QXmppRosterManager.Both) {
                return "Both";
            }
        }
    }

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
                spacing: 5

                Text {
                    text: "JID"
                    width: 80
                    style: Text.Normal
                    anchors.verticalCenter: parent.verticalCenter
                    font { family: "Arial"; pixelSize: 14 }
                }

                Rectangle {
                    width: 300
                    height: 25

                    Text {
                        id: jidField

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
                    text: "Nickname"
                    width: 80
                    style: Text.Normal
                    anchors.verticalCenter: parent.verticalCenter
                    font { family: "Arial"; pixelSize: 14 }
                }

                Rectangle {
                    width: 300
                    height: 25

                    TextInput {
                        id: nicknameField

                        anchors.fill: parent
                        font { family: "Arial"; pixelSize: 16 }
                    }
                }
            }

            Row {
                spacing: 5

                Text {
                    text: "Subscription"
                    width: 80
                    style: Text.Normal
                    anchors.verticalCenter: parent.verticalCenter
                    font { family: "Arial"; pixelSize: 14 }
                }

                Rectangle {
                    width: 100
                    height: 25

                    Text {
                        id: subField
                        anchors.fill: parent
                        font { family: "Arial"; pixelSize: 16 }
                    }
                }

                Button {
                    id: subscribeButton

                    width: 90
                    height: 25
                    text: "Sub"
                    onClicked: {
                        root.rosterManager.subscribe(jid);
                    }
                }

                Button {
                    id: unsubscribeButton

                    width: 90
                    height: 25
                    text: "Unsub"
                    onClicked: root.rosterManager.unsubscribe(jid);
                }
            }

            Row {
                spacing: 5

                Text {
                    text: "Groups"
                    width: 80
                    anchors.verticalCenter: parent.verticalCenter
                    style: Text.Normal
                    font { family: "Arial"; pixelSize: 14 }
                }

                Rectangle {
                    width: 300
                    height: 50

                    TextInput {
                        id: groupsField

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
                    id: applyButton

                    width: 100
                    height: 30
                    text: "Apply"
                    onClicked: {
                        var groups = groupsField.text.split(";");
                        var nickname = nicknameField.text;
                        console.log("Groups:" + groups);
                        console.log("Nickname:" + nickname);
                        //  Doesn't work properly, due to asynchronous sending stanzas
                        //rosterManager.renameItem(root.jid, nickname);
                        //rosterManager.setGroups(root.jid, groups);
                        rosterManager.addItem(root.jid, nickname, groups);
                        root.apply();
                    }
                }

                Button {
                    id: cancelButton

                    width: 100
                    height: 30
                    text: "Cancel"
                    onClicked: root.cancel();
                }
            }
        }
    }
}
