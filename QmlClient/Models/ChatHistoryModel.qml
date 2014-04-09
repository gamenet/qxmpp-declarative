import QtQuick 1.1
import "./ChatHistoryModel.js" as Js

Item {
    id: root

    property string jid
    property variant model: ListModel {
    }

    function addEntry(from, entry) {
        Js.addHistoryEvent(from, entry);
        if (from == jid) {
            model.append(entry);
        }
    }

    onJidChanged: {
        model.clear();
        var entries = Js.get(jid);
        for(var i = 0 ; i < entries.length; i++) {
            model.append(entries[i]);
        }
    }
}
