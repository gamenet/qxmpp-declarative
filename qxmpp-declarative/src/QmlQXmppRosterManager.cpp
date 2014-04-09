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

#include <QmlQXmppRosterManager.h>

#include <Windows.h>
#include <QDebug>

#define SIGNAL_CONNECT_CHECK(X) { bool result = X; Q_ASSERT_X(result, __FUNCTION__ , #X); }

QmlQXmppRosterManager::QmlQXmppRosterManager(QXmppRosterManager *rosterMgr)
  : _rosterManager(rosterMgr)
{
  this->connectSignals();
}

QmlQXmppRosterManager::~QmlQXmppRosterManager()
{

}

QStringList QmlQXmppRosterManager::getRosterBareJids() const
{
  Q_ASSERT(_rosterManager);
 
  return _rosterManager->getRosterBareJids();
}

QmlQXmppPresence* QmlQXmppRosterManager::getPresence(const QString &bareJid, const QString &resource)
{
  Q_ASSERT(_rosterManager);

  QmlQXmppPresence *presence = new QmlQXmppPresence(_rosterManager->getPresence(bareJid,  resource));
  return presence;
}

QString QmlQXmppRosterManager::getNickname(const QString &bareJid)
{
  Q_ASSERT(_rosterManager);

  QXmppRosterIq::Item rosterItem = _rosterManager->getRosterEntry(bareJid);
  return rosterItem.name();
}

int QmlQXmppRosterManager::getSubscription(const QString &bareJid)
{
  Q_ASSERT(_rosterManager);

  QXmppRosterIq::Item rosterItem = _rosterManager->getRosterEntry(bareJid);
  return static_cast<int>(rosterItem.subscriptionType());
}

QStringList QmlQXmppRosterManager::getGroups(const QString &bareJid)
{
  Q_ASSERT(_rosterManager);

  QStringList groupsList;
  QXmppRosterIq::Item rosterItem = _rosterManager->getRosterEntry(bareJid);
  QSet<QString> itemGroups = rosterItem.groups();
  foreach(QString groupName, itemGroups) {
    groupsList << groupName;
  }
  return groupsList;
}

bool QmlQXmppRosterManager::acceptSubscription(const QString &bareJid, const QString &reason)
{
  Q_ASSERT(_rosterManager);

  return _rosterManager->acceptSubscription(bareJid, reason);
}

bool QmlQXmppRosterManager::refuseSubscription(const QString &bareJid, const QString &reason)
{
  Q_ASSERT(_rosterManager);

  return _rosterManager->refuseSubscription(bareJid, reason);
}

bool QmlQXmppRosterManager::subscribe(const QString &bareJid, const QString &reason)
{
  Q_ASSERT(_rosterManager);

  return _rosterManager->subscribe(bareJid, reason);
}

bool QmlQXmppRosterManager::unsubscribe(const QString &bareJid, const QString &reason)
{
  Q_ASSERT(_rosterManager);

  return _rosterManager->unsubscribe(bareJid, reason);
}

bool QmlQXmppRosterManager::addItem(const QString &bareJid, const QString &name, const QStringList &groups)
{
  Q_ASSERT(_rosterManager);

  QSet<QString> groupsSet;
  foreach(QString groupName, groups) {
    groupsSet.insert(groupName);
  }
  
  return _rosterManager->addItem(bareJid, name, groupsSet);
}

bool QmlQXmppRosterManager::removeItem(const QString &bareJid)
{
  Q_ASSERT(_rosterManager);

  return _rosterManager->removeItem(bareJid);
}

bool QmlQXmppRosterManager::renameItem(const QString &bareJid, const QString &name)
{
  Q_ASSERT(_rosterManager);

  return _rosterManager->renameItem(bareJid, name);
}

void QmlQXmppRosterManager::setNickname(const QString &bareJid, const QString &name)
{
  this->renameItem(bareJid, name);
}

void QmlQXmppRosterManager::setGroups(const QString &bareJid, const QStringList &groups)
{
  Q_ASSERT(_rosterManager);

  //qDebug() << "QmlQXmppRosterManager::setGroups()";

  QSet<QString> groupsSet;
  foreach(QString groupName, groups) {
    groupsSet.insert(groupName);
  }
  QString currentNickName = this->getNickname(bareJid);
  //qDebug() << "\t\tCurrent nickname: " << currentNickName;
  _rosterManager->addItem(bareJid, currentNickName, groupsSet);
}

void QmlQXmppRosterManager::connectSignals()
{
  Q_ASSERT(_rosterManager);

  SIGNAL_CONNECT_CHECK(connect(_rosterManager, SIGNAL(rosterReceived()), this, SIGNAL(rosterReceived())));
  SIGNAL_CONNECT_CHECK(connect(_rosterManager, SIGNAL(presenceChanged(const QString&, const QString&)), this, SIGNAL(presenceChanged(const QString&, const QString&))));
  SIGNAL_CONNECT_CHECK(connect(_rosterManager, SIGNAL(subscriptionReceived(const QString&)), this, SIGNAL(subscriptionReceived(const QString&))));
  SIGNAL_CONNECT_CHECK(connect(_rosterManager, SIGNAL(itemAdded(const QString&)), this, SIGNAL(itemAdded(const QString&))));
  SIGNAL_CONNECT_CHECK(connect(_rosterManager, SIGNAL(itemChanged(const QString&)), this, SIGNAL(itemChanged(const QString&))));
  SIGNAL_CONNECT_CHECK(connect(_rosterManager, SIGNAL(itemRemoved(const QString&)), this, SIGNAL(itemRemoved(const QString&))));
}
