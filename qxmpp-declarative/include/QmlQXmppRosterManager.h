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

#include <QmlQXmppPresence.h>
#include <QXmppRosterManager.h>

class QmlQXmppRosterManager : public QObject
{
  Q_OBJECT
  Q_ENUMS(SubscriptionType)

public:
  enum SubscriptionType {
    None = 0,   ///< the user does not have a subscription to the
    ///< contact's presence information, and the contact does
    ///< not have a subscription to the user's presence information
    From = 1,   ///< the contact has a subscription to the user's presence information,
    ///< but the user does not have a subscription to the contact's presence information
    To = 2,     ///< the user has a subscription to the contact's presence information,
    ///< but the contact does not have a subscription to the user's presence information
    Both = 3   ///< both the user and the contact have subscriptions to each
  };

  QmlQXmppRosterManager(QXmppRosterManager *rosterMgr, QObject *parent = 0);
  ~QmlQXmppRosterManager();

  Q_INVOKABLE QStringList getRosterBareJids() const;
  Q_INVOKABLE QmlQXmppPresence* getPresence(const QString &bareJid, const QString &resource);
  Q_INVOKABLE QString getNickname(const QString &bareJid);
  //  Returns int instead of enum due to QTBUG-23543 https://bugreports.qt-project.org/browse/QTBUG-23543
  //  Q_INVOKABLE SubscriptionType getSubscription(const QString &bareJid);
  Q_INVOKABLE int getSubscription(const QString &bareJid);
  Q_INVOKABLE QStringList getGroups(const QString &bareJid);

public slots:
  //  QXmpp slots
  bool acceptSubscription(const QString &bareJid, const QString &reason = QString());
  bool refuseSubscription(const QString &bareJid, const QString &reason = QString());
  bool subscribe(const QString &bareJid, const QString &reason = QString());
  bool unsubscribe(const QString &bareJid, const QString &reason = QString());

  //  maybe refactor these methods
  bool addItem(const QString &bareJid, const QString &name = QString(), const QStringList &groups = QStringList());
  bool removeItem(const QString &bareJid);
  bool renameItem(const QString &bareJid, const QString &name);

  //  Problems when sequentially calling both methods - responce doesn't received when second method is called
  //  So using add item is preferrable now.
  void setNickname(const QString &bareJid, const QString &name);
  void setGroups(const QString &bareJid, const QStringList &groups);

signals:
  /// This signal is emitted when the Roster IQ is received after a successful
  /// connection. That is the roster entries are empty before this signal is emitted.
  /// One should use getRosterBareJids() and getRosterEntry() only after
  /// this signal has been emitted.
  void rosterReceived();

  /// This signal is emitted when the presence of a particular bareJid and resource changes.
  void presenceChanged(const QString& bareJid, const QString& resource);

  /// This signal is emitted when a contact asks to subscribe to your presence.
  ///
  /// You can either accept the request by calling acceptSubscription() or refuse it
  /// by calling refuseSubscription().
  ///
  /// \note If you set QXmppConfiguration::autoAcceptSubscriptions() to true, this
  /// signal will not be emitted.
  void subscriptionReceived(const QString& bareJid, const QString& reason);

  /// This signal is emitted when the roster entry of a particular bareJid is
  /// added as a result of roster push.
  void itemAdded(const QString& bareJid);

  /// This signal is emitted when the roster entry of a particular bareJid
  /// changes as a result of roster push.
  void itemChanged(const QString& bareJid);

  /// This signal is emitted when the roster entry of a particular bareJid is
  /// removed as a result of roster push.
  void itemRemoved(const QString& bareJid);

private:
  void connectSignals();

private:
  QXmppRosterManager *_rosterManager;
};
