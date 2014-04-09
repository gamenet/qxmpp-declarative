.pragma library


var historyListModels = {};

//debug

//var testData = [
//            {
//                "when": "21.04.2013 - 16:42",
//                "body": "Hi!"
//            },
//            {
//                "when": "21.04.2013 - 16:43",
//                "body": "Hi!"
//            },
//            {
//                "when": "21.04.2013 - 16:44",
//                "body": "Hi!"
//            },
//                    {
//                        "type": "msg",
//                        "when": "21.04.2013 - 16:45",
//                        "body": "Hi!"
//                    },
//                    {
//                        "type": "msg",
//                        "when": "21.04.2013 - 16:47",
//                        "body": "Bla-bla-bla"
//                    }
//        ];

// end debug

var history = {};
//history["bs.player_1"] = [
//            {
//                "type": "msg",
//                "when": "21.04.2013 - 16:42",
//                "body": "bs.player_1 - Hi!"
//            },
//            {
//                "type": "msg",
//                "when": "21.04.2013 - 16:47",
//                "body": "bs.player_1 - Bla-bla-bla"
//            }
//        ];

//history["bs.player_2"] = [
//            {
//                "type": "msg",
//                "when": "21.04.2013 - 09.01",
//                "body": "bs.player_2 - sdgjngvwer;knvberjk;v;"
//            },
//            {
//                "type": "msg",
//                "when": "21.04.2013 - 10.00",
//                "body": "bs.player_2 - KGVkqjhbeclqjebhfqwei;buqwui;fb"
//            }
//        ];

function addHistoryEvent(jid, event) {
    var historyElement = {};
    if(!jid || !event) {
        return;
    }

    if (!history.hasOwnProperty(jid)) {
        history[jid] = [];
    }

    console.log(history[jid].length);

    if (event.hasOwnProperty("type")) {
        historyElement.body = event["type"];
    }
    if(event.hasOwnProperty("body")) {
        historyElement.body = event["body"];
    }
    if(event.hasOwnProperty("when")) {
        historyElement.when = event["when"];
    }
    history[jid].push(historyElement);
}

function clearHistory(jid) {
    if (!history.hasOwnProperty(jid)) {
        history[jid] = [];
    }
}

function get(jid) {
    if (jid && history.hasOwnProperty(jid)) {
        return history[jid];
    }
    return [];
}
