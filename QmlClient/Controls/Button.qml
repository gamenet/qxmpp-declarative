import QtQuick 1.1

Rectangle {
    id: root

    property alias text: buttonText.text
    property variant style: ButtonStyleColors {}
    property bool enabled: true
	property bool buttonPressed: false

    signal entered()
    signal exited()
    signal pressed(variant mouse)
    signal clicked(variant mouse)

    color: root.style.normal

    Behavior on color {
        PropertyAnimation { duration: 100 }
    }

    Text {
        id: buttonText

        anchors.centerIn: parent
        //color: "#FFFFFF"
        font {
            family: "Arial"
            pixelSize: 16
        }
    }

    StateGroup {
        states: [
            State {
                name: ""
                PropertyChanges { target: root; color: root.style.normal}
            },
            State {
                name: "Hover"
                when: mouseArea.containsMouse && !root.inProgress
                PropertyChanges { target: root; color: root.style.hover}
            },
            State {
                name: "Disabled"
                when: !root.enabled
                PropertyChanges { target: root; color: root.style.disabled; opacity: 0.2}
            }
        ]
    }

    MouseArea {
        id: mouseArea

        anchors.fill: parent

        hoverEnabled: true
        enabled: root.enabled

        onPressed: {
            root.pressed(mouse);
            root.buttonPressed = true;
        }
        onReleased: {
            if (root.enabled && root.buttonPressed) {
                root.buttonPressed = false;
                root.clicked(mouse);
            }
        }
        onEntered: {
            root.entered();
        }
        onExited: {
            root.exited();
        }
    }
}
