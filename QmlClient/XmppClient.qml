import QtQuick 1.1
import QXmpp 1.0
import 'scripts/utils.js' as Utils
import 'scripts/NicknameCache.js' as NicknameCache
import 'scripts/AvatarProvider.js' as AvatarProvider
import 'scripts/Utility.js' as Utility

Item {
    id: root

    property string server: "j.gamenet.dev"
    property string user
    property string password
    property int xmppError: 0
    property bool isConnected: false
    property alias rosterManager: client.rosterManager
    property alias vCardManager: client.vcardManager
    property alias archiveManager: client.archiveManager

    property bool acceptSubscription: true

    signal connected()
    signal disconnected()
    signal messageReceived(string from, string message)
    signal statusChanged(string from, int type, string text)

    //  Subscribtion
    signal subscribtionRequested(string from)

    //  Roster management
    signal contactAdded(string bareJid)
    signal contactChanged(string bareJid)
    signal contactRemoved(string bareJid)

    function connect() {
        var bareJid = user + "@" + server;
        client.connectToServer(bareJid, password);
    }

    function disconnect() {
        client.disconnectFromServer();
    }

    function sendMessage(bareJid, messageText) {
        client.sendMessage(bareJid, messageText);
    }

    //  contact management
    function addContact(bareJid, nickname, groups) {
        client.rosterManager.addItem(bareJid, nickname, groups);
    }

    function removeContact(bareJid) {
        client.rosterManager.removeItem(bareJid);
    }

   function subscribe(bareJid, reason) {
        client.rosterManager.client.subscribe(bareJid, reason);
    }

    function unsubscribe(bareJid, reason) {
        client.rosterManager.client.unsubscribe(bareJid, reason);
    }

    QXmppClient {
        id: client

//        logger: QXmppLogger {
//            loggingType: QXmppLogger.FileLogging
//            logFilePath: "D:\XmppClient.log"
//            messageTypes: QXmppLogger.AnyMessage
//        }

        onConnected: {
            root.isConnected = true;
            console.log("Connected to server ");
            root.connected();
        }

        onDisconnected: {
            root.isConnected = false;
            console.log("Disconnected from server j.");
            root.disconnected();
        }

        onMessageReceived: {
           console.log("Received message: " + from);
           console.log("\tmessage: " + body);
           //console.log("\textra: " + message.extra.test);
        }


        //        onError: {
        ////            if (error == XmppClient.SocketError) {
        ////                console.log("Error due to TCP socket.");
        ////            } else if (error == XmppClient.KeepAliveError) {
        ////                console.log("Error due to no response to a keep alive.");
        ////            } else if (error == XmppClient.XmppStreamError) {
        ////                console.log("Error due to XML stream.");
        ////            }
        //        }
        //        onPresenceReceived: {
        ////            var presenceString = "";
        ////            if (presence.type == XmppPresence.Online) {
        ////                // The entity or resource is online.
        ////                presenceString = "Online";
        ////            } else if (presence.type == XmppPresence.Away) {
        ////                // The entity or resource is temporarily away.
        ////                presenceString = "Away";
        ////            } else if (presence.type == XmppPresence.XA) {
        ////                // The entity or resource is away for an extended period.
        ////                presenceString = "XA";
        ////            } else if (presence.type == XmppPresence.DND) {
        ////                // The entity or resource is busy ("Do Not Disturb").
        ////                presenceString = "DND";
        ////            } else if (presence.type == XmppPresence.Chat) {
        ////                // The entity or resource is actively interested in chatting.
        ////                presenceString = "Chat";
        ////            } else if (presence.type == XmppPresence.Invisible) {
        ////                // obsolete XEP-0018: Invisible Presence
        ////                presenceString = "Invisible";
        ////            }
        ////            console.log("Presence received: " + presenceString + ", status: " + presence.statusText);
        //        }
    }

    Connections {
        target: client.rosterManager

//        onSubscriptionReceived: {
//            // If we have a subscription to the requester, accept
//            // reciprocal subscription.
//            //
//            // FIXME: use QXmppRosterIq::Item::To and QXmppRosterIq::Item::Both
//            var subscription = item.client.subscriptionType(bareJid);
//            if (subscription == 2 || subscription == 3) {
//                // accept subscription
//                client.rosterManager.acceptSubscription(bareJid);
//                return;
//            }
//        }

        onRosterReceived: {
            console.log("Roster received: ");

            var rosterUsers = client.rosterManager.getRosterBareJids();
            for (var i = 0; i < rosterUsers.length; i++) {
                root.contactAdded(rosterUsers[i]);
//                client.vcardManager.requestVCard(rosterUsers[i]);
//                //  автоматическая подписка
//                if (root.automaticSubscription) {
//                    console.log("Trying to subscribe: " + rosterUsers[i] + "@j.gamenet.dev");
//                    client.rosterManager.subscribe(rosterUsers[i], "I want you to add to my subs list");
//                }
            }
        }

        onPresenceChanged: {
            //console.log("Presence changed: bareJid == " + bareJid + ", resource: " + resource);
            var presence = client.rosterManager.getPresence(bareJid, resource);
            if (presence) {
                if (presence.type == QXmppPresence.Offline) {
                    console.log("Presence: Offline");
                } else if (presence.type == QXmppPresence.Online) {
                    console.log("Presence: Online");
                } else if (presence.type == QXmppPresence.Away) {
                    console.log("Presence: Away");
                } else if (presence.type == QXmppPresence.XA) {
                    console.log("Presence: XA");
                } else if (presence.type == QXmppPresence.DND) {
                    console.log("Presence: DND");
                } else if (presence.type == QXmppPresence.Chat) {
                    console.log("Presence: Chat");
                } else if (presence.type == QXmppPresence.Invisible) {
                    console.log("Presence: Invisible");
                }
                root.statusChanged(bareJid, presence.type, presence.status);
            }
        }

        onSubscriptionReceived: {
            console.log("Received subscription request from: " + bareJid);
            root.subscribtionRequested(bareJid);
//            if (acceptSubscription) {
//                console.log("Accepted!");
//                client.rosterManager.acceptSubscription(bareJid);
//                client.rosterManager.subscribe(bareJid);
//            } else {
//                console.log("Refused!");
//                client.rosterManager.refuseSubscription(bareJid);
//                client.rosterManager.unsubscribe(bareJid);
//            }
        }
        onItemAdded: {
            console.log("Roster item added: " + bareJid);
            root.contactAdded(bareJid);
        }
        onItemChanged: {
            console.log("Roster item changed: " + bareJid);

            console.log("New nickname: " + client.rosterManager.getNickname(bareJid));

            root.contactChanged(bareJid);
        }
        onItemRemoved: {
            console.log("Roster item removed: " + bareJid);
            root.contactRemoved(bareJid);
        }
    }

    Connections {
        target: client.vcardManager

        onVCardReceived: {
            console.log("Vcard received for: " + vcard.from);
        }
    }

//    Connections {
//        target: client.archieveManager

//        //on
//    }
}
