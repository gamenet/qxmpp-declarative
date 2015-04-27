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
#include <QtCore/QStringList>
#include <QtCore/QHash>
#include <QtCore/QVariant>
#include <QtCore/QVariantMap>

#include <QXmppDataForm.h>
#include <QXmppMucIq.h>

class QXmppMucManager;
class QXmppMucRoom;
class QXmppDataForm;
class QXmppMessage;
class QXmppClient;

class QmlQXmppMessage;

class QmlQXmppMucManager : public QObject
{
  Q_OBJECT
public:
  QmlQXmppMucManager(QXmppMucManager *manager, QXmppClient* client, QObject *parent = 0);
  virtual ~QmlQXmppMucManager();

public slots:
  QStringList getRooms();
  void addRoom(const QString& roomJid);

  bool requestConfiguration(const QString& roomJid);
  bool requestPermissions(const QString& roomJid);

  bool destroyRoom(const QString& roomJid, const QString& reason = QString());

  bool join(const QString& roomJid, const QString& nickname, const QVariantMap& options);
  bool leave(const QString& roomJid, const QString &message = QString());

  bool ban(const QString& roomJid, const QString &occupantJid, const QString &reason);
  bool kick(const QString& roomJid, const QString &occupantJid, const QString &reason);

  QStringList participants(const QString& roomJid) const;
  QStringList participantsFullJid(const QString& roomJid) const;
  QString participantFullJid(const QString& roomJid, const QString& occupantJid) const;

  bool sendInvitation(const QString& roomJid, const QString &jid, const QString &reason);
  bool sendInvitationMediated(const QString& roomJid, const QString &jid, const QString &reason);
  bool sendMessage(const QString& roomJid, const QString &text);

  QString subject(const QString& roomJid) const;
  void setSubject(const QString& roomJid, const QString &subject);

  bool setConfiguration(const QString& roomJid, const QVariantMap &form);
  bool setPermission(const QString& roomJid, const QString jid, const QString affliation);

signals:
  /// This signal is emitted when an invitation to a chat room is received.
  void invitationReceived(const QString &roomJid, const QString &inviter, const QString &reason);

  /// This signal is emitted when a new room is managed.
  void roomAdded(const QString& roomJid);

  void roomCreated(const QString& roomJid);

  /// This signal is emitted once you have joined the room.
  void joined(const QString& roomJid);

  /// This signal is emitted if you get kicked from the room.
  void kicked(const QString& roomJid, const QString &jid, const QString &reason);

  /// This signal is emitted once you have left the room.
  void left(const QString& roomJid);

  /// This signal is emitted when the room's human-readable name changes.
  void nameChanged(const QString& roomJid, const QString &name);

  /// This signal is emitted when your own nick name changes.
  void nickNameChanged(const QString& roomJid, const QString &nickName);

  /// This signal is emitted when the configuration form for the room is received.
  void configurationReceived(const QString& roomJid, const QVariantMap &configuration);

  /// This signal is emitted when the room's permissions are received.
  void permissionsReceived(const QString& roomJid, const QVariantList &permissions);

  void messageReceived(const QString& roomJid, QmlQXmppMessage *message);

  /// This signal is emitted when a participant joins the room.
  void participantAdded(const QString& roomJid, const QString &jid);

  /// This signal is emitted when a participant changes.
  void participantChanged(const QString& roomJid, const QString &jid);

  /// This signal is emitted when a participant leaves the room.
  void participantRemoved(const QString& roomJid, const QString &jid);

  void participantPermissions(const QString& roomJid, const QString &jid, const QVariantMap &permissions);

private slots:
  void onRoomAdded(QXmppMucRoom *room);
  void onRoomDestroyed(QObject *object);
  void onRoomCreated();

  void onJoinedRoom();
  void onKicked(const QString &jid, const QString &reason);
  void onLeft();
  void onNameChanged(const QString &name);

  void onConfigurationReceived(const QXmppDataForm &configuration);
  void onMessageReceived(const QXmppMessage &message);
  void onPermissionsReceived(const QList<QXmppMucItem> &permissions);

  void onParticipantPermissions(const QString &jid, const QXmppMucItem& permissions);

  /// This signal is emitted when a participant joins the room.
  void onParticipantAdded(const QString &jid);
  void onParticipantChanged(const QString &jid);
  void onParticipantRemoved(const QString &jid);

private:
  QXmppMucManager *_manager;
  QXmppClient *_client;
  QHash<QString, QXmppMucRoom *> _rooms;
  QHash<QString, QString> _fullConfigNameToShort;
  QHash<QString, QXmppDataForm::Field::Type> _configTypes;

  QVariantMap _defaultConfigValue;

  void initConfigMap();
  void setShortConfig(const QString& fullName, const QString& shortName, const QVariant& defaultValue, QXmppDataForm::Field::Type type);
  void appendField(QList<QXmppDataForm::Field> &fields, const QString& key, const QVariant& value, QXmppDataForm::Field::Type type);
};
