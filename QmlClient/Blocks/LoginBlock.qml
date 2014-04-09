import QtQuick 1.1
import "../Controls"

Item {
    id: root

    property bool isConnected: false
    property bool inProgress: false
    property alias user: userInput.text
    property alias password: passwordInput.text

    signal login()
    signal logout()
    signal cancel()

    Column {
        spacing: 5

        Row {
            spacing: 10
            Text {
                text: "User: "
                width: 100
                height: 25
                style: Text.Normal
                font { family: "Arial"; pixelSize: 14 }
            }

            Rectangle {
                width: 200
                height: 25

                TextInput {
                    id: userInput

                    anchors.fill: parent
                    font { family: "Arial"; pixelSize: 16 }
                }

            }
        }

        Row {
            spacing: 10

            Text {
                text: "Password:"
                width: 100
                height: 25
                style: Text.Normal
                font { family: "Arial"; pixelSize: 14 }
            }

            Rectangle {
                width: 200
                height: 25

                TextInput {
                    id: passwordInput

                    anchors.fill: parent
                    font { family: "Arial"; pixelSize: 16 }
                }
            }
        }

        Row {
            spacing: 20

            Button {
                id: loginButton

                width: 100
                height: 30
                text: "Login"

                onClicked: {
                    if (root.isConnected) {
                        root.logout();
                    } else {
                        root.login();
                    }
                }
            }
            Button {
                id: cancelButton

                width: 100
                height: 30
                text: "Cancel"

                MouseArea {
                    anchors.fill: parent
                    onClicked: {
                        root.cancel();
                    }

                }
            }
        }
    }

    StateGroup {
        states: [
            State {
                name: "Offline"
                when: !root.isConnected && !root.inProgress
                PropertyChanges {
                    target: loginButton
                    text: "Log In"
                }
            },
            State {
                name: "Connecting"
                when: !root.isConnected && root.inProgress
                PropertyChanges {
                    target: loginButton
                    enabled: false
                }
            },
            State {
                name: "Online"
                when: root.isConnected && !root.inProgress
                PropertyChanges {
                    target: loginButton
                    text: "Log Out"
                }
            }
        ]
    }
}
