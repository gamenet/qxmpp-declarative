import QtQuick 1.1
import "../Controls"

Item {
    id: root

    signal addContact()
    signal editContact()
    signal removeContact()
    signal viewVCard()

    Row {
        width: parent.width
        height: 20
        spacing: 10

        IconButton {
            width: 20
            height: 20
            image: "../images/Buttons/add.png"
            onClicked: root.addContact();
        }
        IconButton {
            width: 20
            height: 20
            image: "../images/Buttons/options.png"
            onClicked: root.editContact();
        }
        IconButton {
            width: 20
            height: 20
            image: "../images/Buttons/vcard.png"
            onClicked: root.viewVCard();
        }
        IconButton {
            width: 20
            height: 20
            image: "../images/Buttons/remove.png"
            onClicked: root.removeContact();
        }
    }
}
