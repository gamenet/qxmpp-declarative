import QtQuick 1.1
import QXmpp 1.0
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
    property alias statusType: client.statusType
    property alias statusText: client.statusText

    signal connected()
    signal disconnected()
    signal messageReceived(string from, string message)
    signal statusChanged(string from, string type, string text)

    //  Subscribtion
    signal subscribtionRequested(string from)

    //  Roster management
    signal contactAdded(string bareJid)
    signal contactChanged(string bareJid)
    signal contactRemoved(string bareJid)

    function connect() {
        var bareJid = user + "@" + server;

        //  connect using configuration params
        client.configuration.host = "j.gamenet.dev";
        client.configuration.domain = "j.gamenet.dev";
        client.configuration.user = root.user;
        client.configuration.password = root.password;
        client.connectUsingConfiguration();

        //  simple connect, using only JID and password
        //client.connectToServer(bareJid, password);
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
            console.log("\tmessage: " + message);
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

        onPresenceReceived: {
            root.statusChanged(presence.from, presence.type, presence.status);
        }
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
            //console.log("ROSTER MANAGER: Roster received");

            var rosterUsers = client.rosterManager.getRosterBareJids();
            for (var i = 0; i < rosterUsers.length; i++) {
                root.contactAdded(rosterUsers[i]);
                //                client.vcardManager.requestVCard(rosterUsers[i]);
            }
        }

        onPresenceChanged: {
            //console.log("Presence changed: bareJid == " + bareJid + ", resource: " + resource);
            var presence = client.rosterManager.getPresence(bareJid, resource);
            if (presence) {
                root.statusChanged(bareJid, presence.type, presence.status);
            }
        }

        onSubscriptionReceived: {
            //console.log("Received subscription request from: " + bareJid);
            root.subscribtionRequested(bareJid);
        }
        onItemAdded: {
            //console.log("Roster item added: " + bareJid);
            root.contactAdded(bareJid);
        }
        onItemChanged: {
            //console.log("Roster item changed: " + bareJid);
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
