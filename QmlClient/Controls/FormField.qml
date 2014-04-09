import QtQuick 1.1

Item {
    id: root

    property alias caption: captionText.text
    property alias value: valueField.text
    property alias readOnly: valueField.readOnly

    Row {
        spacing: 5

        Text {
            id: captionText

            width: 100
            height: 25
            anchors.verticalCenter: parent.verticalCenter
            style: Text.Normal
            smooth: true
            font { family: "Arial"; pixelSize: 16 }
            text: root.caption
        }

        Rectangle {
            width: root.width - 105
            height: 25
            anchors.verticalCenter: parent.verticalCenter

            TextInput {
                id: valueField

                anchors.margins: 3
                anchors.fill: parent
                text: root.value
                font { family: "Arial"; pixelSize: 16 }
            }
        }
    }
}
