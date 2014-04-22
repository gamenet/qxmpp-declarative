import QtQuick 1.1

Item {
    id: root

    property alias caption: captionText.text
    property int captionWidth: 105
    property alias text: valueField.text
    property alias readOnly: valueField.readOnly

    Row {
        spacing: 5

        Text {
            id: captionText

            width: captionWidth - 5
            height: 25
            style: Text.Normal
            smooth: true
            font { family: "Arial"; pixelSize: 16 }
            text: root.caption
        }

        Rectangle {
            width: root.width - captionWidth
            height: root.height

            TextInput {
                id: valueField

                anchors.margins: 3
                anchors.fill: parent
                font { family: "Arial"; pixelSize: 16 }
            }
        }
    }
}
