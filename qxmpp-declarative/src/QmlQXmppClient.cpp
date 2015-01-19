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

#include <QXmppUtils.h>
#include <QXmppMessage.h>
#include <QXmppPresence.h>
#include <QXmppArchiveManager.h>
#include <QXmppVCardManager.h>
#include <QXmppLastActivityManager.h>
#include <QXmppMessageCarbonsIq.h>

#include <QmlQXmppPlugin_global.h>
#include <QmlQXmppClient.h>
#include <QmlQXmppMessage.h>
#include <QmlQXmppPresence.h>
#include <QmlQXmppConfiguration.h>
#include <QmlQXmppArchiveManager.h>
#include <QmlQXmppRosterManager.h>
#include <QmlQXmppVCardManager.h>
#include <QmlQXmppLastActivityManager.h>
#include <QmlQXmppPEPManager.h>

QmlQXmppClient::QmlQXmppClient(QDeclarativeItem *parent)
    : QDeclarativeItem(parent)
    , _archiveManager(0)
    , _archiveManagerWrapper(0)
    , _rosterManagerWrapper(0)
    , _vcardManagerWrapper(0)
    , _lastActivityManagerWrapper(0)
    , _pepManagerWrapper(0)
{
  connectSignals();
}

QmlQXmppClient::~QmlQXmppClient()
{
}

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
  if (!this->_vcardManagerWrapper) {
    //  removing QXmpp vCard manager implementation
    QXmppClientExtension *extension = this->_client.findExtension<QXmppVCardManager>();
    this->_client.removeExtension(extension);

    this->_vcardManagerWrapper = new QmlQXmppVCardManager;
    this->_client.addExtension(this->_vcardManagerWrapper);
  }

  return this->_vcardManagerWrapper;
}

QmlQXmppLastActivityManager *QmlQXmppClient::lastActivityManager()
{
  if (!this->_lastActivityManagerWrapper) {
    this->_lastActivityManagerWrapper = new QmlQXmppLastActivityManager;
    this->_client.addExtension(this->_lastActivityManagerWrapper);
  }

  return this->_lastActivityManagerWrapper;
}


QmlQXmppPEPManager *QmlQXmppClient::pepManager()
{
  if (!this->_pepManagerWrapper)
    this->_pepManagerWrapper = new QmlQXmppPEPManager(&this->_client.pepManager(), this);

  return this->_pepManagerWrapper;
}


QmlQXmppClient::StatusType QmlQXmppClient::clientStatusType()
{
  return this->availableStatusTypeToStatusType(this->_client.clientPresence().availableStatusType());
}

QString QmlQXmppClient::clientStatusText()
{
  return this->_client.clientPresence().statusText();
}

void QmlQXmppClient::connectUsingConfiguration()
{
  this->_client.connectToServer(this->_configuration);
}

void QmlQXmppClient::connectToServer(const QString &jid, const QString &password, const QVariantMap &options)
{
  QXmppConfiguration config;
  config.setJid(jid);
  config.setPassword(password);

  if (options.contains(QString("resource")))
    config.setResource(options["resource"].toString());

  if (options.contains(QString("streamManagementMode")))
    config.setStreamManagementMode(static_cast<QXmppConfiguration::StreamManagementMode>(options["streamManagementMode"].toInt()));
  
  this->_client.connectToServer(config);
}

void QmlQXmppClient::disconnectFromServer()
{
 emit this->_client.streamManagementEnabled(false);
 this->_client.disconnectFromServer();
}

void QmlQXmppClient::sendMessage(const QString& bareJid, QVariantMap map)
{
  QXmppMessage msg;

  if (map.contains(QString("body")))
    msg.setBody(map["body"].toString());
  
  if (map.contains(QString("type")))
    msg.setType(QmlQXmppMessage::parseMessageType(map["type"].toInt()));

  if (map.contains(QString("state")))
    msg.setState(QmlQXmppMessage::parseMessageState(map["state"].toInt()));

  if (map.contains(QString("attentionRequest")))
    msg.setAttentionRequested(map["attentionRequest"].toBool());
  
  QStringList resources = this->_client.rosterManager().getResources(bareJid);
  if (!resources.isEmpty()) {
    for (int i = 0; i < resources.size(); ++i) {
      msg.setTo(bareJid + "/" + resources.at(i));
      this->_client.sendPacket(msg);
    }
  } else {
    msg.setTo(bareJid);
    this->_client.sendPacket(msg);
  }
}

void QmlQXmppClient::setClientPresence(QVariantMap map)
{
  bool anythingChanged = false;
  QXmppPresence presence = this->_client.clientPresence();
  
  if (map.contains(QString("type"))) {
    QXmppPresence::AvailableStatusType newType = intToAvailableStatusType(map["type"].toInt());
    if (newType != presence.availableStatusType()) {
        presence.setAvailableStatusType(newType);
        anythingChanged = true;
    }
  }

  if (map.contains(QString("text"))) {
    QString newStatus = map["text"].toString();
    if (newStatus != presence.statusText()) {
      presence.setStatusText(newStatus);
      anythingChanged = true;
    }
  }

  if (anythingChanged) 
    this->_client.setClientPresence(presence);
}

void QmlQXmppClient::onConnected()
{
  //  activate XEP-280 Message Carbons capability
  QXmppMessageCarbonsIq carbonIq;
  this->_client.sendPacket(carbonIq);

  emit this->connected();
}

void QmlQXmppClient::onError(QXmppClient::Error code)
{
  emit error(static_cast<int>(code));
}

void QmlQXmppClient::onMessageReceived(const QXmppMessage& message)
{
  if (message.hasMessageCarbon()) {
    QmlQXmppMessage qmlmessage(message.carbonMessage());
    emit carbonMessageReceived(&qmlmessage);
    return;
  }

  QmlQXmppMessage qmlmessage(message);
  emit messageReceived(&qmlmessage);
}

void QmlQXmppClient::onPresenceReceived(const QXmppPresence &presence)
{
  if (QXmppUtils::jidToBareJid(presence.from()) == this->_client.configuration().jidBare()) {
    emit this->clientStatusTypeChanged();
    emit this->clientStatusTextChanged();
  }

  QmlQXmppPresence presenceWrapper(presence);
  emit this->presenceReceived(&presenceWrapper);
}

void QmlQXmppClient::connectSignals()
{
  SIGNAL_CONNECT_CHECK(connect(&this->_client, SIGNAL(error(QXmppClient::Error)), this, SLOT(onError(QXmppClient::Error))));
  SIGNAL_CONNECT_CHECK(connect(&this->_client, SIGNAL(connected()), this, SLOT(onConnected())));
  SIGNAL_CONNECT_CHECK(connect(&this->_client, SIGNAL(disconnected()), this, SIGNAL(disconnected())));
  SIGNAL_CONNECT_CHECK(connect(&this->_client, SIGNAL(messageReceived(const QXmppMessage &)), this, SLOT(onMessageReceived(const QXmppMessage &))));
  SIGNAL_CONNECT_CHECK(connect(&this->_client, SIGNAL(presenceReceived(const QXmppPresence &)), this, SLOT(onPresenceReceived(const QXmppPresence &))));
  QObject::connect(&this->_client, &QXmppClient::streamManagementResumed, this, &QmlQXmppClient::streamManagementResumed);
}

QXmppPresence::AvailableStatusType QmlQXmppClient::intToAvailableStatusType(int value)
{
  switch (value) {
  case QmlQXmppClient::Online:
    return QXmppPresence::Online;
  case QmlQXmppClient::Away:
    return QXmppPresence::Away;
  case QmlQXmppClient::XA:
    return QXmppPresence::XA;
  case QmlQXmppClient::DND:
    return QXmppPresence::DND;
  case QmlQXmppClient::Chat:
    return QXmppPresence::Chat;
  case QmlQXmppClient::Invisible:
    return QXmppPresence::Invisible;
  }
  return QXmppPresence::Online;
}

QmlQXmppClient::StatusType QmlQXmppClient::availableStatusTypeToStatusType(QXmppPresence::AvailableStatusType type)
{
  switch (type) {
  case QXmppPresence::Online:
    return QmlQXmppClient::Online;
  case QXmppPresence::Away:
    return QmlQXmppClient::Away;
  case QXmppPresence::XA:
    return QmlQXmppClient::XA;
  case QXmppPresence::DND:
    return QmlQXmppClient::DND;
  case QXmppPresence::Chat:
    return QmlQXmppClient::Chat;
  case QXmppPresence::Invisible:
    return QmlQXmppClient::Invisible;
  }
  return QmlQXmppClient::Online;
}
