import QtQuick 1.1

import QtQuick 1.1
import QXmpp 1.0
import "../Models"
import "../Controls"

Rectangle {
    id: root

    property variant vCardManager
    property string jid
    property bool readOnly

    signal ok()

    onJidChanged: {
        if (jid == "") {
            return;
        }
    }

    border {
        color: "#000000"
        width: 2
    }
    color: "#EEEEEE"
    anchors.margins: 5

    Item {
        anchors.fill: parent
        anchors.margins: 5

        Column {
            spacing: 5
            anchors.fill: parent

//            Row {
//                Image {
//                    id: userAvatar

//                    width: 48
//                    height: 48
//                    fillMode: Image.PreserveAspectFit
//                    source: "image://xmppimageprovider/" + xmppClient.getVCardProperty(currentJid, "PHOTO");
//                }
//            }

            FormField {
                id: firstNameField

                readOnly: root.readOnly
                width: 390
                height: 30
                caption: "First name:"
            }
            FormField {
                id: middleNameField

                readOnly: root.readOnly
                width: 390
                height: 30
                caption: "Middle name:"
            }
            FormField {
                id: lastNameField

                readOnly: root.readOnly
                width: 390
                height: 30
                caption: "Last name:"
            }
            FormField {
                id: fullNameField

                readOnly: root.readOnly
                width: 390
                height: 30
                caption: "Full name:"
            }
            FormField {
                id: emailField

                readOnly: root.readOnly
                width: 390
                height: 30
                caption: "email:"
            }
            FormField {
                id: birthdayField

                readOnly: root.readOnly
                width: 390
                height: 30
                caption: "Birthday:"
            }
            Item {
                width: 390
                height: 30

                Button {
                    id: applyButton

                    anchors.centerIn: parent
                    width: 100
                    height: 30
                    text: "Ok"
                    onClicked: root.ok();
                }
            }
        }
    }
}
