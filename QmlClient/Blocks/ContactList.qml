import QtQuick 1.1
import QXmpp 1.0
import "../Models"
import "../Controls" as Controls
import "../scripts/Utility.js" as Utility
import "../scripts/AvatarProvider.js" as AvatarProvider

Column {
    id: root

    property string current: extendedModel.get(d.currentContact).jid || ""

    signal contactClicked(string jid)
    signal contactDoubleClicked(string jid)

    function addContact(bareJid) {
        extendedModel.append({"jid": bareJid,
                                 "nickname": bareJid,
                                 "avatar": AvatarProvider.getAvatar(Utility.jidToUser(bareJid)),
                                 "status": "offline",
                                 "statusText": "",
                                 "hasNewMessages": false});
    }

    function removeContact(bareJid) {
        extendedModel.removeById(bareJid);
    }

    function setNickname(bareJid, nickname) {
        extendedModel.setPropertyById(bareJid, "nickname", nickname);
    }

    function nickname(){
        var item = extendedModel.getById(bareJid);
        if (item) {
            return item.nickname || "";
        }
        return "";
    }

    function setStatusType(bareJid, type) {
        extendedModel.setPropertyById(bareJid, "status", type);
    }

    function statusType(bareJid) {
        var item = extendedModel.getById(bareJid);
        if (item) {
            return item.status || "";
        }
        return "";
    }

    function setStatusText(bareJid, text) {
        extendedModel.setPropertyById(bareJid, "statusText", text);
    }

    function statusText(bareJid) {
        var item = extendedModel.getById(bareJid);
        if (item) {
            return item.statusText || "";
        }
        return "";
    }

    function setNewMessages(bareJid, hasNewMsg) {
        extendedModel.setPropertyById(bareJid, "hasNewMessages", hasNewMsg);
    }

    spacing: 10

    QtObject {
        id: d
        property int currentContact
    }

    ListView {
        id: listView

        width: parent.width
        height: parent.height - addContactBlock.height - 40
        spacing: 10
        interactive: false
        clip: true
        delegate: ContactListDelegate {
            isCurrent: model.index == d.currentContact
        }
        model: extendedModel.model

        ExtendedListModel {
            id: extendedModel

            idProperty: "jid"
        }

        MouseArea {
            anchors.fill: parent
            onClicked: {
                var index = listView.indexAt(mouseX, mouseY);
                if (index >= 0) {
                    d.currentContact = index;
                    root.contactClicked(root.current);
                }
            }

            onDoubleClicked: {
                var item;
                var index = listView.indexAt(mouseX, mouseY);
                if (index >= 0) {
                    d.currentContact = index;
                    root.setNewMessages(root.current, false);
                    root.contactDoubleClicked(root.current);
                }
            }
        }
    }
}
