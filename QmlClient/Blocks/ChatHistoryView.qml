import QtQuick 1.1

ListView {
    id: listview

    delegate: Rectangle {
        width: listview.width
        height: 25

        Text {
            x: 5
            anchors.verticalCenter: parent.verticalCenter
            width: 200
            height: 20
            text: model.when + ": " + model.body
        }
    }
}
