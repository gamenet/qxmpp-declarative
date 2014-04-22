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
    if (sub == QXmppRosterManager.None) {
        return "None";
    }
    if (sub == QXmppRosterManager.From) {
        return "From";
    }
    if (sub == QXmppRosterManager.To) {
        return "To";
    }
    if (sub == QXmppRosterManager.Both) {
        return "Both";
    }
    return "None";
}

function jidToUser(jid) {
    var pos = jid.indexOf('@');
    if (pos < 0)
        return '';
    return jid.substring(0, pos);
}
