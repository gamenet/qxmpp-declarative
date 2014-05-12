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

#include <QtDeclarative/QDeclarativeEngine>

#include <QXmppMessage.h>
#include <QXmppPresence.h>
#include <QXmppArchiveManager.h>

#include <QmlQXmppPlugin_global.h>
#include <QmlQXmppClient.h>
#include <QmlQXmppMessage.h>
#include <QmlQXmppPresence.h>
#include <QmlQXmppConfiguration.h>
#include <QmlQXmppArchiveManager.h>
#include <QmlQXmppRosterManager.h>
#include <QmlQXmppVCardManager.h>

QmlQXmppClient::QmlQXmppClient(QObject *parent)
    : QObject(parent)
    , _archiveManager(0)
    , _archiveManagerWrapper(0)
    , _rosterManagerWrapper(0)
    , _vcardManagerWrapper(0)
{
  connectSignals();
}

QmlQXmppClient::~QmlQXmppClient()
{
}
//
QmlQXmppConfiguration *QmlQXmppClient::configuration()
{
  if (!this->_configurationWrapper) {
    this->_configurationWrapper = new QmlQXmppConfiguration(&this->_configuration);
  }
  return this->_configurationWrapper;
}

QmlQXmppArchiveManager *QmlQXmppClient::archiveManager()
{
  if (!this->_archiveManager) {
    this->_archiveManager = new QXmppArchiveManager;
    this->_client.addExtension(this->_archiveManager);
  }

  //if (!this->_archiveManagerWrapper)
  //  this->_archiveManagerWrapper = new QmlQXmppArchiveManager(&this->_client.arcManager(), this);

  return _archiveManagerWrapper;
}

//
QmlQXmppRosterManager *QmlQXmppClient::rosterManager()
{
  if (!this->_rosterManagerWrapper)
    this->_rosterManagerWrapper = new QmlQXmppRosterManager(&this->_client.rosterManager(), this);

  return this->_rosterManagerWrapper;
}

QmlQXmppVCardManager *QmlQXmppClient::vcardManager()
{
  if (!this->_vcardManagerWrapper)
    this->_vcardManagerWrapper = new QmlQXmppVCardManager(&this->_client.vCardManager(), this);
 
  return this->_vcardManagerWrapper;
}

QString QmlQXmppClient::clientStatusType()
{
  if (this->_client.clientPresence().type() == QXmppPresence::Available) {
    return QmlQXmppPresence::statusToString(this->_client.clientPresence().availableStatusType());
  } else {
    return "offline";
  }
}

void QmlQXmppClient::setClientStatusType(const QString &value)
{
  if (value != this->clientStatusType()) {
    QXmppPresence presence = this->_client.clientPresence();
    if (value == "offline") {
      presence.setType(QXmppPresence::Unavailable);
    } else {
      presence.setType(QXmppPresence::Available);
      presence.setAvailableStatusType(QmlQXmppPresence::stringToStatus(value));
    }
    this->_client.setClientPresence(presence);

    emit statusTypeChanged(value);
  }
}

QString QmlQXmppClient::clientStatusText()
{
  return this->_client.clientPresence().statusText();
}

void QmlQXmppClient::setClientStatusText(const QString &value)
{
  if (value != this->clientStatusText()) {
    QXmppPresence presence = this->_client.clientPresence();
    presence.setStatusText(value);
    this->_client.setClientPresence(presence);

    emit statusTextChanged(value);
  }
}

void QmlQXmppClient::connectUsingConfiguration()
{
  this->_client.connectToServer(this->_configuration);
}

void QmlQXmppClient::connectToServer(const QString &jid, const QString &password)
{
 this->_client.connectToServer(jid, password);
}

void QmlQXmppClient::disconnectFromServer()
{
 this->_client.disconnectFromServer();
}

void QmlQXmppClient::sendMessage(const QString& bareJid, const QString& message)
{
 this->_client.sendMessage(bareJid, message);
}

void QmlQXmppClient::onMessageReceived(const QXmppMessage& message)
{
  QmlQXmppMessage qmlmessage;
  qmlmessage = message;
  emit messageReceived(&qmlmessage);
}

void QmlQXmppClient::onPresenceReceived(const QXmppPresence &presence)
{
  QmlQXmppPresence *presenceWrapper = new QmlQXmppPresence(presence);
  emit presenceReceived(presenceWrapper);
}

void QmlQXmppClient::connectSignals()
{
  SIGNAL_CONNECT_CHECK(connect(&this->_client, SIGNAL(error(QXmppClient::Error)), this, SIGNAL(error(QXmppClient::Error))));
  SIGNAL_CONNECT_CHECK(connect(&this->_client, SIGNAL(connected()), this, SIGNAL(connected())));
  SIGNAL_CONNECT_CHECK(connect(&this->_client, SIGNAL(disconnected()), this, SIGNAL(disconnected())));
  SIGNAL_CONNECT_CHECK(connect(&this->_client, SIGNAL(messageReceived(const QXmppMessage &)), this, SLOT(onMessageReceived(const QXmppMessage &))));
  SIGNAL_CONNECT_CHECK(connect(&this->_client, SIGNAL(presenceReceived(const QXmppPresence &)), this, SLOT(onPresenceReceived(const QXmppPresence &))));
}