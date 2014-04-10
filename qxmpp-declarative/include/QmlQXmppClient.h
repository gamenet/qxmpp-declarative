/*
 * Copyright (C) 2014 qxmpp-declarative developers
 *
 * Author:
 *  Nikita Gorbunov
 *
 * Source:
 *  https://github.com/n-gorbunov/qxmpp-declarative
 *
 * This file is a part of qxmpp-declarative library.
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 */

#pragma once

#include <QtCore/QObject>

#include <QXmppClient.h>

class QmlQXmppMessage;
class QmlQXmppPresence;
class QmlQXmppArchiveManager;
class QmlQXmppRosterManager;
class QmlQXmppVCardManager;

class QXmppArchiveManager;

class QmlQXmppClient : public QObject
{
  Q_OBJECT
   Q_PROPERTY(QmlQXmppArchiveManager* archiveManager READ archiveManager CONSTANT)
   Q_PROPERTY(QmlQXmppRosterManager* rosterManager READ rosterManager CONSTANT)
   Q_PROPERTY(QmlQXmppVCardManager* vcardManager READ vcardManager CONSTANT)

   Q_PROPERTY(QString statusType READ clientStatusType WRITE setClientStatusType NOTIFY statusTypeChanged)
   Q_PROPERTY(QString statusText READ clientStatusText WRITE setClientStatusText NOTIFY statusTextChanged)

public:
    QmlQXmppClient(QObject *parent = 0);
    ~QmlQXmppClient();

    QmlQXmppArchiveManager *archiveManager();
    QmlQXmppRosterManager *rosterManager();
    QmlQXmppVCardManager* vcardManager();

    QString clientStatusType();
    void setClientStatusType(const QString &value);

    QString clientStatusText();
    void setClientStatusText(const QString &value);

signals:
    /// This signal is emitted when the client connects successfully to the XMPP
    /// server i.e. when a successful XMPP connection is established.
    /// XMPP Connection involves following sequential steps:
    ///     - TCP socket connection
    ///     - Client sends start stream
    ///     - Server sends start stream
    ///     - TLS negotiation (encryption)
    ///     - Authentication
    ///     - Resource binding
    ///     - Session establishment
    ///
    /// After all these steps a successful XMPP connection is established and
    /// connected() signal is emitted.
    ///
    /// After the connected() signal is emitted QXmpp will send the roster request
    /// to the server. On receiving the roster, QXmpp will emit
    /// QXmppRosterManager::rosterReceived(). After this signal, QXmppRosterManager object gets
    /// populated and you can use rosterManager() to get the handle of QXmppRosterManager object.
    void connected();

    /// This signal is emitted when the XMPP connection disconnects.
    void disconnected();

    /// This signal is emitted when the XMPP connection encounters any error.
    /// The QXmppClient::Error parameter specifies the type of error occurred.
    /// It could be due to TCP socket or the xml stream or the stanza.
    /// Depending upon the type of error occurred use the respective get function to
    /// know the error.
    void error(QXmppClient::Error);

    void messageReceived(QString from, QString message);
        
    //  This signal is emitted when client presence type changes.
    void presenceReceived(QmlQXmppPresence *presence);

    //  This signal is emitted when client status type changes.
    void statusTypeChanged(const QString &type);

    //  This signal is emitted when client status text changes.
    void statusTextChanged(const QString &text);

public slots:
    void connectToServer(const QString &jid, const QString &password);
    void disconnectFromServer();
    void sendMessage(const QString& bareJid, const QString& message);


private slots:
    void onMessageReceived(const QXmppMessage& message);
    void onPresenceReceived(const QXmppPresence &presence);

private:
  void connectSignals();

private:
  QXmppClient *_client;
  QXmppArchiveManager *_archiveManager;

  QmlQXmppPresence *_clientPresence;
   QmlQXmppArchiveManager *_archiveManagerWrapper;
   QmlQXmppRosterManager *_rosterManagerWrapper;
   QmlQXmppVCardManager* _vcardManagerWrapper;
};
