QXmpp QML Plugin
=================

QML plugin binding for [QXmpp](https://github.com/qxmpp-project/qxmpp) library

# INSTALLATION

    $ git clone https://github.com/ricardomv/qxmpp-qml-plugin
    $ mkdir build
    $ cd build/
    $ qmake ..
    $ make
    # make install

# USAGE

    import QXmpp 1.0

# EXAMPLE

    QXmppClient {
        id: xmppClient
        configuration.host: "xmpp.example.com"
        configuration.jid: "username"
        configuration.password: "password"

        onConnected: {
            console.log("Connected to server.")
        }
        onMessageReceived: {
            console.log(message.from + ": " + message.body)
        }
    }
    Component.onCompleted: xmppClient.connectUsingConfiguration()