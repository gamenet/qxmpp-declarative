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
#include <QtDeclarative/QDeclarativeEngine>

#include <QXmppmessage.h>
#include <QXmppArchiveManager.h>

#include <QmlQXmppClient.h>
#include <QmlQXmppPresence.h>
#include <QmlQXmppArchiveManager.h>
#include <QmlQXmppRosterManager.h>
#include <QmlQXmppVCardManager.h>

#define SIGNAL_CONNECT_CHECK(X) { bool result = X; Q_ASSERT_X(result, __FUNCTION__ , #X); }

QmlQXmppClient::QmlQXmppClient(QObject *parent)
    : QObject(parent)
    , _client(new QXmppClient(this))
    , _archiveManager(0)
    , _archiveManagerWrapper(0)
    , _rosterManagerWrapper(0)
    , _vcardManagerWrapper(0)
{
  connectSignals();
}

QmlQXmppClient::~QmlQXmppClient()
{
  if (_rosterManagerWrapper)
    delete _rosterManagerWrapper;
  if (_vcardManagerWrapper)
    delete _vcardManagerWrapper;
}
//
QmlQXmppArchiveManager *QmlQXmppClient::archiveManager()
{
  Q_ASSERT(_client);

  if (!_archiveManager) {
    _archiveManager = new QXmppArchiveManager;
    _client->addExtension(_archiveManager);
  }

  //if (!_archiveManagerWrapper)
  //  _archiveManagerWrapper = new QmlQXmppArchiveManager(&_client->arcManager());

  return _archiveManagerWrapper;
}

//
QmlQXmppRosterManager *QmlQXmppClient::rosterManager()
{
  if (!_rosterManagerWrapper)
    _rosterManagerWrapper = new QmlQXmppRosterManager(&_client->rosterManager());

  return _rosterManagerWrapper;
}

QmlQXmppVCardManager *QmlQXmppClient::vcardManager()
{
  if (!_vcardManagerWrapper)
    _vcardManagerWrapper = new QmlQXmppVCardManager(&_client->vCardManager());
 
  return _vcardManagerWrapper;
}

void QmlQXmppClient::connectToServer(const QString &jid, const QString &password)
{
 Q_ASSERT(_client);

 _client->connectToServer(jid, password);
}

void QmlQXmppClient::disconnectFromServer()
{
 Q_ASSERT(_client);

 _client->disconnectFromServer();
}

void QmlQXmppClient::sendMessage(const QString& bareJid, const QString& message)
{
 Q_ASSERT(_client);

 _client->sendMessage(bareJid, message);
}

void QmlQXmppClient::onMessageReceived(const QXmppMessage& message)
{
  //QmlQXmppMessage incomingMessage;
  //incomingMessage = message;
  //emit messageReceived(&incomingMessage);
  emit messageReceived(message.from(), message.body());
}

void QmlQXmppClient::onPresenceReceived(const QXmppPresence &presence)
{
  QmlQXmppPresence presenceWrapper(presence);
  emit presenceReceived(&presenceWrapper);
}

void QmlQXmppClient::connectSignals()
{
  Q_ASSERT(_client);

  SIGNAL_CONNECT_CHECK(connect(_client, SIGNAL(error(QXmppClient::Error)), this, SIGNAL(error(QXmppClient::Error))));
  SIGNAL_CONNECT_CHECK(connect(_client, SIGNAL(connected()), this, SIGNAL(connected())));
  SIGNAL_CONNECT_CHECK(connect(_client, SIGNAL(disconnected()), this, SIGNAL(disconnected())));
  SIGNAL_CONNECT_CHECK(connect(_client, SIGNAL(messageReceived(const QXmppMessage &)), this, SLOT(onMessageReceived(const QXmppMessage &))));
  SIGNAL_CONNECT_CHECK(connect(_client, SIGNAL(presenceReceived(const QXmppPresence &)), this, SLOT(onPresenceReceived(const QXmppPresence &))));
}

