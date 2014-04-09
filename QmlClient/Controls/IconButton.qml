import QtQuick 1.1

Rectangle {
    id: root

    property alias image: icon.source
    property bool enabled: true

    signal entered()
    signal exited()
    signal pressed(variant mouse)
    signal clicked(variant mouse)

    color: "#00FFFFFF"

    QtObject {
        id: d
        property bool buttonPressed: false
    }

    Image {
        id: icon

        anchors.centerIn: parent
    }

    StateGroup {
        states: [
            State {
                name: ""
                PropertyChanges { target: root; color: "#00FFFFFF"}
            },
            State {
                name: "Hover"
                when: mouseArea.containsMouse
                PropertyChanges { target: root; color: "#DDDDDD"}
            },
            State {
                name: "Disabled"
                when: !root.enabled
                PropertyChanges { target: root; color: "#DDDDDD"; opacity: 0.2}
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
            d.buttonPressed = true;
        }
        onReleased: {
            if (root.enabled && d.buttonPressed) {
                d.buttonPressed = false;
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
