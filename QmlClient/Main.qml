import QtQuick 1.1
import "./Blocks" as Blocks
import "./Models" as Models

Rectangle {
    id: root

    width: 400
    height: 800
    color: "#CCCCCC"

    XmppClient {
        id: xmppClient

        onConnected: {
            console.log("Client connected");
        }
        onDisconnected: {
            console.log("Client disconnected");
            d.currentJid  = "";
        }
        onStatusChanged: {
            contactList.setStatusType(from, type);
            contactList.setStatusText(from, text);
        }
        onContactAdded: {
            contactList.addContact(bareJid);
            //if (properties.hasOwnProperty("nickname")) {
            //rosterModel.setNickname(jid, NicknameCache.getNickname(rosterUsers[i]));
            //rosterModel.setStatusType(jid, Utility.presenceToString(QXmppPresence.Online));
        }
        onContactRemoved: {
            contactList.removeContact(bareJid);
        }
        onSubscribtionRequested: {
            subscriptionBlock.jid = from;
            onlineGui.state = "SubscriptionRequest";
        }
    }

    QtObject {
        id: d

        property string currentJid: ""
    }

    Column {
        spacing: 5
        width: parent.width

        Blocks.LoginBlock {
            id: loginDialog

            width: root.width
            height: 100
            user: "nikita.gorbunov"
            password: "123"

            onLogin: {
                console.log("onAccepted: " + loginDialog.user);
                xmppClient.user = loginDialog.user;
                xmppClient.password = loginDialog.password;
                xmppClient.connect();
            }
            onLogout: {
                xmppClient.disconnect();
            }
            onCancel: {
                Qt.quit();
            }
        }

        Item {
            id: onlineGui

            width: parent.width

            Column {
                spacing: 5
                width: parent.width

                Blocks.MenuBlock {
                    id: menuBlock

                    width: parent.width
                    height: 25
                    onAddContact: {
                        onlineGui.state = "AddingNewContact";
                    }
                    onEditContact: {
                        if (d.currentJid != "") {
                            onlineGui.state = "EditingContact";
                        }
                    }
                    onRemoveContact: {
                        if (d.currentJid != "") {
                            xmppClient.rosterManager.removeItem(d.currentJid);
                            d.currentJid = "";
                        }
                    }
                    onViewVCard: {
                        if (d.currentJid != "") {
                            onlineGui.state = "ViewingVCard";
                        }
                    }
                }

                Blocks.SubscriptionRequest {
                    id: subscriptionBlock

                    width: root.width
                    height: 100
                    visible: false
                    onAccepted: {
                        xmppClient.rosterManager.acceptSubscription(subscriptionBlock.jid);
                        onlineGui.state = "";
                    }
                    onRefused: {
                        xmppClient.rosterManager.refuseSubscription(subscriptionBlock.jid);
                        onlineGui.state = "";
                    }
                }

                Blocks.AddContactBlock {
                    id: addContactBlock

                    width: root.width
                    height: 80
                    visible: false
                    onAddContact: {
                        xmppClient.rosterManager.addItem(jid);
                        onlineGui.state = "";
                    }
                    onCancel: {
                        onlineGui.state = "";
                    }
                }

                Blocks.EditContactBlock {
                    id: editcontactBlock

                    width: root.width
                    height: 200
                    visible: false
                    rosterManager: xmppClient.rosterManager
                    jid: d.currentJid
                    onApply: {
                        onlineGui.state = "";
                    }
                    onCancel: {
                        onlineGui.state = "";
                    }
                }

                Blocks.VCardView {
                    id: vcardBlock
                    visible: false

                    width: parent.width
                    height: 250
                    onOk: {
                        onlineGui.state = "";
                    }
                }

                Blocks.ContactList {
                    id: contactList

                    width: parent.width
                    height: 350
                    visible: true
                    onContactClicked: {
                        d.currentJid = jid;
                    }
                    onContactDoubleClicked: {
                        onlineGui.state = "Chatting";
                    }
                }

                Blocks.ChatBlock {
                    id: chatBlock

                    historyModel: historyModel
                    visible: false
                    width: root.width

                    jid: d.currentJid

                    onSendMessage: {
                        xmppClient.sendMessage(d.currentChatJid, message);
                    }
                    onCancel: {
                        onlineGui.state = "";
                    }
                }
            }

            states: [
                State {
                    name: "AddingNewContact"
                    PropertyChanges {
                        target: addContactBlock
                        visible: true
                    }
                },
                State {
                    name: "Chatting"
                    PropertyChanges {
                        target: chatBlock
                        visible: true
                    }
                },
                State {
                    name: "EditingContact"
                    PropertyChanges {
                        target: editcontactBlock
                        visible: true
                    }
                },
                State {
                    name: "ViewingVCard"
                    PropertyChanges {
                        target: vcardBlock
                        visible: true
                        readOnly: true
                    }
                },
                State {
                    name: "SubscriptionRequest"
                    PropertyChanges {
                        target: subscriptionBlock
                        visible: true
                    }
                },
                State {
                    name: "EditingMyVCard"
                    PropertyChanges {
                        target: vcardBlock
                        visible: true
                        readOnly: false
                    }
                }
            ]
        }
    }

    Models.ChatHistoryModel {
        id: historyModel

        jid: d.jid || ""
    }

    StateGroup {
        state: "Offline"
        states: [
            State {
                name: "Offline"
                when: !xmppClient.isConnected && xmppClient.xmppError == 0
                PropertyChanges {
                    target: loginDialog
                    visible: true
                }
                PropertyChanges {
                    target: onlineGui
                    visible: false
                }
            },
            State {
                name: "Online"
                when: xmppClient.isConnected
                PropertyChanges {
                    target: loginDialog
                    visible: false
                }
                PropertyChanges {
                    target: onlineGui
                    visible: true
                }
            }
        ]
    }
}

