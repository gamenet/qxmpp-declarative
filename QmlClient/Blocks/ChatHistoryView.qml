import QtQuick 1.1

//import "./models/ChatHistoryModel.js" as History

ListView {
    id: listview

    delegate: Rectangle {
        width: listview.width
        height: 25

        Text {
            id: messageText

            x: 5
            anchors.verticalCenter: parent.verticalCenter
            width: 200
            height: 20
            text: model.when + ": " + model.body
        }
    }
}
