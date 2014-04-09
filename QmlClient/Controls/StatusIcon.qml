import QtQuick 1.1


Image {
    id: root

    fillMode: Image.PreserveAspectFit
    states: [
        State {
            name: "offline"
            PropertyChanges {
                target: root
                source: "../images/StatusIcon/offline.png"
            }
        },
        State {
            name: "online"
            PropertyChanges {
                target: root
                source: "../images/StatusIcon/online.png"
            }
        },
        State {
            name: "away"
            PropertyChanges {
                target: root
                source: "../images/StatusIcon/away.png"
            }
        },
        State {
            name: "xa"
            PropertyChanges {
                target: root
                source: "../images/StatusIcon/xa.png"
            }
        },
        State {
            name: "dnd"
            PropertyChanges {
                target: root
                source: "../images/StatusIcon/dnd.png"
            }
        },
        State {
            name: "chat"
            PropertyChanges {
                target: root
                source: "../images/StatusIcon/chat.png"
            }
        }
    ]
}
