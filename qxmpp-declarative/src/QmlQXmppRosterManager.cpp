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

#include <QmlQXmppPlugin_global.h>
#include <QmlQXmppRosterManager.h>

QmlQXmppRosterManager::QmlQXmppRosterManager(QXmppRosterManager *rosterMgr, QObject *parent)
  : QObject(parent)
  , _rosterManager(rosterMgr)
{
  this->connectSignals();
}

QmlQXmppRosterManager::~QmlQXmppRosterManager()
{

}

QStringList QmlQXmppRosterManager::getRosterBareJids() const
{
  Q_ASSERT(this->_rosterManager);
 
  return this->_rosterManager->getRosterBareJids();
}

QmlQXmppPresence* QmlQXmppRosterManager::getPresence(const QString &bareJid, const QString &resource)
{
  Q_ASSERT(this->_rosterManager);

  QmlQXmppPresence *presence = new QmlQXmppPresence(this->_rosterManager->getPresence(bareJid,  resource));
  return presence;
}

QString QmlQXmppRosterManager::getNickname(const QString &bareJid)
{
  Q_ASSERT(this->_rosterManager);

  QXmppRosterIq::Item rosterItem = this->_rosterManager->getRosterEntry(bareJid);
  return rosterItem.name();
}

int QmlQXmppRosterManager::getSubscription(const QString &bareJid)
{
  Q_ASSERT(this->_rosterManager);

  QXmppRosterIq::Item rosterItem = this->_rosterManager->getRosterEntry(bareJid);
  return static_cast<int>(rosterItem.subscriptionType());
}

QStringList QmlQXmppRosterManager::getGroups(const QString &bareJid)
{
  Q_ASSERT(this->_rosterManager);

  QStringList groupsList;
  QXmppRosterIq::Item rosterItem = this->_rosterManager->getRosterEntry(bareJid);
  QSet<QString> itemGroups = rosterItem.groups();
  foreach(QString groupName, itemGroups) {
    groupsList << groupName;
  }
  return groupsList;
}

bool QmlQXmppRosterManager::acceptSubscription(const QString &bareJid, const QString &reason)
{
  Q_ASSERT(this->_rosterManager);

  return this->_rosterManager->acceptSubscription(bareJid, reason);
}

bool QmlQXmppRosterManager::refuseSubscription(const QString &bareJid, const QString &reason)
{
  Q_ASSERT(this->_rosterManager);

  return this->_rosterManager->refuseSubscription(bareJid, reason);
}

bool QmlQXmppRosterManager::subscribe(const QString &bareJid, const QString &reason)
{
  Q_ASSERT(this->_rosterManager);

  return this->_rosterManager->subscribe(bareJid, reason);
}

bool QmlQXmppRosterManager::unsubscribe(const QString &bareJid, const QString &reason)
{
  Q_ASSERT(this->_rosterManager);

  return this->_rosterManager->unsubscribe(bareJid, reason);
}

bool QmlQXmppRosterManager::addItem(const QString &bareJid, const QString &name, const QStringList &groups)
{
  Q_ASSERT(this->_rosterManager);

  QSet<QString> groupsSet;
  foreach(QString groupName, groups) {
    groupsSet.insert(groupName);
  }
  
  return this->_rosterManager->addItem(bareJid, name, groupsSet);
}

bool QmlQXmppRosterManager::removeItem(const QString &bareJid)
{
  Q_ASSERT(this->_rosterManager);

  return this->_rosterManager->removeItem(bareJid);
}

bool QmlQXmppRosterManager::renameItem(const QString &bareJid, const QString &name)
{
  Q_ASSERT(this->_rosterManager);

  return this->_rosterManager->renameItem(bareJid, name);
}

void QmlQXmppRosterManager::setNickname(const QString &bareJid, const QString &name)
{
  this->renameItem(bareJid, name);
}

void QmlQXmppRosterManager::setGroups(const QString &bareJid, const QStringList &groups)
{
  Q_ASSERT(this->_rosterManager);

  QSet<QString> groupsSet;
  foreach(QString groupName, groups) {
    groupsSet.insert(groupName);
  }
  QString currentNickName = this->getNickname(bareJid);
  this->_rosterManager->addItem(bareJid, currentNickName, groupsSet);
}

void QmlQXmppRosterManager::connectSignals()
{
  Q_ASSERT(this->_rosterManager);

  SIGNAL_CONNECT_CHECK(connect(this->_rosterManager, SIGNAL(rosterReceived()), this, SIGNAL(rosterReceived())));
  SIGNAL_CONNECT_CHECK(connect(this->_rosterManager, SIGNAL(presenceChanged(const QString&, const QString&)), 
    this, SIGNAL(presenceChanged(const QString&, const QString&))));

  SIGNAL_CONNECT_CHECK(connect(this->_rosterManager, SIGNAL(subscriptionReceived(const QString&, const QString&)), 
    this, SIGNAL(subscriptionReceived(const QString&, const QString&))));

  SIGNAL_CONNECT_CHECK(connect(this->_rosterManager, SIGNAL(itemAdded(const QString&)), this, SIGNAL(itemAdded(const QString&))));
  SIGNAL_CONNECT_CHECK(connect(this->_rosterManager, SIGNAL(itemChanged(const QString&)), this, SIGNAL(itemChanged(const QString&))));
  SIGNAL_CONNECT_CHECK(connect(this->_rosterManager, SIGNAL(itemRemoved(const QString&)), this, SIGNAL(itemRemoved(const QString&))));
}
