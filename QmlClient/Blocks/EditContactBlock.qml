import QtQuick 1.1
import QXmpp 1.0
import "../Models"
import "../Controls"
import "../scripts/Utility.js" as UtilityJS

Item {
    id: root

    property alias color: contentRectangle.color

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
        subField.text = UtilityJS.subscriptionToString(rosterManager.getSubscription(jid));
        groupsField.text = rosterManager.getGroups(jid).join(";");
    }

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
                        id: jidField

                        width: 390
                        height: 25
                        caption: "JID"
                        captionWidth: 90
                        text: root.jid
                    }
                    FormField {
                        id: nicknameField

                        width: 390
                        height: 25
                        caption: "Nickname"
                        captionWidth: 90
                    }

                    Row {
                        spacing: 5

                        FormField {
                            id: subField

                            width: 200
                            height: 25
                            caption: "Subscribtion"
                            captionWidth: 90
                        }

                        Button {
                            id: subscribeButton

                            width: 90
                            height: 25
                            text: "Sub"
                            onClicked: root.rosterManager.subscribe(jid);
                        }

                        Button {
                            id: unsubscribeButton

                            width: 90
                            height: 25
                            text: "Unsub"
                            onClicked: root.rosterManager.unsubscribe(jid);
                        }
                    }

                    FormField {
                        id: groupsField

                        width: 390
                        height: 25
                        caption: "Groups"
                        captionWidth: 90
                    }

                    Row {
                        spacing: 5

                        Item {
                            width: 85
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
    }
}
