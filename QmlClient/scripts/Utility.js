function presenceToString(presence) {
    var result = "Offline";

    if (presence == QXmppPresence.Offline) {
        result =  "Offline";
    } else if (presence == QXmppPresence.Online) {
        result = "Online";
    } else if (presence == QXmppPresence.Away) {
        result = "Away";
    } else if (presence == QXmppPresence.XA) {
        result = "XA";
    } else if (presence == QXmppPresence.DND) {
        result = "DND";
    } else if (presence == QXmppPresence.Chat) {
        result = "Chat";
    } else if (presence == QXmppPresence.Invisible) {
        result = "Invisible";
    }
    return result;
}

function subscriptionToString(sub) {
    //if()
}
