/*
* The MIT License (MIT)
* 
* Copyright (c) 2014 GameNet
* 
* Permission is hereby granted, free of charge, to any person obtaining a copy
* of this software and associated documentation files (the "Software"), to deal
* in the Software without restriction, including without limitation the rights
* to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
* copies of the Software, and to permit persons to whom the Software is
* furnished to do so, subject to the following conditions:
*  
* The above copyright notice and this permission notice shall be included in
* all copies or substantial portions of the Software.
* 
* THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
* IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
* FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
* AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
* LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
* OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
* THE SOFTWARE.
*/

#pragma once

#include <QtCore/QObject>

#include <QXmppClient.h>

class QmlQXmppMessage;
class QmlQXmppPresence;
class QmlQXmppConfiguration;
class QmlQXmppArchiveManager;
class QmlQXmppRosterManager;
class QmlQXmppVCardManager;
class QXmppArchiveManager;

class QmlQXmppClient : public QObject
{
  Q_OBJECT
  Q_PROPERTY(QmlQXmppConfiguration *configuration READ configuration CONSTANT)
  Q_PROPERTY(QmlQXmppArchiveManager* archiveManager READ archiveManager CONSTANT)
  Q_PROPERTY(QmlQXmppRosterManager* rosterManager READ rosterManager CONSTANT)
  Q_PROPERTY(QmlQXmppVCardManager* vcardManager READ vcardManager CONSTANT)
  Q_PROPERTY(QString statusType READ clientStatusType WRITE setClientStatusType NOTIFY statusTypeChanged)
  Q_PROPERTY(QString statusText READ clientStatusText WRITE setClientStatusText NOTIFY statusTextChanged)

public:
  QmlQXmppClient(QObject *parent = 0);
  ~QmlQXmppClient();

  QmlQXmppConfiguration *configuration();
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

  void messageReceived(QmlQXmppMessage* message);

  //  This signal is emitted when client presence type changes.
  void presenceReceived(QmlQXmppPresence *presence);

  //  This signal is emitted when client status type changes.
  void statusTypeChanged(const QString &type);

  //  This signal is emitted when client status text changes.
  void statusTextChanged(const QString &text);

public slots:
  //  connect using QXmppConfiguration params
  void connectUsingConfiguration();
  void connectToServer(const QString &jid, const QString &password);
  void disconnectFromServer();
  void sendMessage(const QString& bareJid, const QString& message);

private slots:
  void onMessageReceived(const QXmppMessage& message);
  void onPresenceReceived(const QXmppPresence &presence);

private:
  void connectSignals();

private:
  QXmppClient _client;
  QXmppConfiguration _configuration;
  QXmppArchiveManager *_archiveManager;

  QmlQXmppPresence *_clientPresence;
  QmlQXmppConfiguration *_configurationWrapper;
  QmlQXmppArchiveManager *_archiveManagerWrapper;
  QmlQXmppRosterManager *_rosterManagerWrapper;
  QmlQXmppVCardManager* _vcardManagerWrapper;
};
