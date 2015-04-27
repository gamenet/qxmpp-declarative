#include <QmlQXmppPlugin_global.h>
#include <QmlQXmppMucManager.h>
#include <QmlQXmppMessage.h>

#include <QXmppMucManager.h>
#include <QXmppMessage.h>
#include <QXmppClient.h>

#include <QtCore/QDebug>

QmlQXmppMucManager::QmlQXmppMucManager(QXmppMucManager *manager, QXmppClient* client, QObject *parent /*= 0*/)
  : _manager(manager)
  , _client(client)
  , QObject(parent)
{
  SIGNAL_CONNECT_CHECK(QObject::connect(
    this->_manager, SIGNAL(roomAdded(QXmppMucRoom *)), 
    this, SLOT(onRoomAdded(QXmppMucRoom *))));

  SIGNAL_CONNECT_CHECK(QObject::connect(
    this->_manager, SIGNAL(invitationReceived(const QString &, const QString &, const QString &)),
    this, SIGNAL(invitationReceived(const QString &, const QString &, const QString &))));

  this->initConfigMap();
}

QmlQXmppMucManager::~QmlQXmppMucManager()
{
}

QStringList QmlQXmppMucManager::getRooms()
{
  QStringList result;
  QList<QXmppMucRoom*> rooms = this->_manager->rooms();
  Q_FOREACH(QXmppMucRoom* room, rooms) {
    result << room->jid();
  }

  return result;
}

void QmlQXmppMucManager::addRoom(const QString& roomJid)
{
  this->_manager->addRoom(roomJid);
}

bool QmlQXmppMucManager::requestConfiguration(const QString& roomJid)
{
  if (!this->_rooms.contains(roomJid))
    return false;

  return this->_rooms[roomJid]->requestConfiguration();
}

bool QmlQXmppMucManager::requestPermissions(const QString& roomJid)
{
  if (!this->_rooms.contains(roomJid))
    return false;

  return this->_rooms[roomJid]->requestPermissions();
}

bool QmlQXmppMucManager::destroyRoom(const QString& roomJid, const QString& reason)
{
  if (!this->_rooms.contains(roomJid))
    return false;

  QXmppMucRoom* room = this->_rooms[roomJid];
  return room->destroy(reason);
}

bool QmlQXmppMucManager::join(const QString& roomJid, const QString& nickname, const QVariantMap& options)
{
  if (!this->_rooms.contains(roomJid))
    return false;

  QXmppMucRoom* room = this->_rooms[roomJid];
  room->setNickName(nickname);
  if (options.contains("password"))
    room->setPassword(options.value("password").toString());

  if (options.contains("history")) {
    QVariantMap historyConfig = options["history"].toMap();
    if (historyConfig.contains("maxchars"))
      room->setHistoryConfig("maxchars", historyConfig.value("maxchars").toString());
    
    if (historyConfig.contains("maxstanzas"))
      room->setHistoryConfig("maxstanzas", historyConfig.value("maxstanzas").toString());

    if (historyConfig.contains("seconds"))
      room->setHistoryConfig("seconds", historyConfig.value("seconds").toString());

    if (historyConfig.contains("since")) {
      QVariant v = historyConfig.value("since");
      QDateTime since = QDateTime::fromMSecsSinceEpoch(historyConfig.value("since").toULongLong());
      QString value = since.toUTC().toString(Qt::ISODate);
      room->setHistoryConfig("since", value);
    }
  }

  return room->join();
}

bool QmlQXmppMucManager::leave(const QString& roomJid, const QString &message /*= QString()*/)
{
  if (!this->_rooms.contains(roomJid))
    return false;

  return this->_rooms[roomJid]->leave(message);
}

bool QmlQXmppMucManager::ban(const QString& roomJid, const QString &occupantJid, const QString &reason)
{
  if (!this->_rooms.contains(roomJid))
    return false;

  return this->_rooms[roomJid]->ban(occupantJid, reason);
}

bool QmlQXmppMucManager::kick(const QString& roomJid, const QString &occupantJid, const QString &reason)
{
  if (!this->_rooms.contains(roomJid))
    return false;

  return this->_rooms[roomJid]->kick(occupantJid, reason);
}

QStringList QmlQXmppMucManager::participants(const QString& roomJid) const
{
  if (!this->_rooms.contains(roomJid))
    return QStringList();

  return this->_rooms[roomJid]->participants();
}

QStringList QmlQXmppMucManager::participantsFullJid(const QString& roomJid) const
{
  if (!this->_rooms.contains(roomJid))
    return QStringList();

  QStringList result;
  QXmppMucRoom* room = this->_rooms[roomJid];
  Q_FOREACH(const QString &occupantJid, room->participants()) {
    QString realJid = room->participantFullJid(occupantJid);
    result << (realJid.isEmpty() ? occupantJid : realJid);
  }

  return result;
}

QString QmlQXmppMucManager::participantFullJid(const QString& roomJid, const QString& occupantJid) const
{
  if (!this->_rooms.contains(roomJid))
    return QString();

  return this->_rooms[roomJid]->participantFullJid(occupantJid);
}

bool QmlQXmppMucManager::sendInvitation(const QString& roomJid, const QString &jid, const QString &reason)
{
  if (!this->_rooms.contains(roomJid))
    return false;

  return this->_rooms[roomJid]->sendInvitation(jid, reason);
}

bool QmlQXmppMucManager::sendInvitationMediated(const QString& roomJid, const QString &jid, const QString &reason)
{
  QXmppMessage message;
  message.setTo(roomJid);
  message.setType(QXmppMessage::Normal);
  message.setMucInvitationJid(jid);
  message.setMucInvitationReason(reason);
  message.setMucInvitationDirect(false);

  return this->_client->sendPacket(message);
}

bool QmlQXmppMucManager::sendMessage(const QString& roomJid, const QString &text)
{
  if (!this->_rooms.contains(roomJid))
    return false;

  return this->_rooms[roomJid]->sendMessage(text);
}

QString QmlQXmppMucManager::subject(const QString& roomJid) const
{
  if (!this->_rooms.contains(roomJid))
    return QString();

  return this->_rooms[roomJid]->subject();
}

void QmlQXmppMucManager::setSubject(const QString& roomJid, const QString &subject)
{
  if (!this->_rooms.contains(roomJid))
    return;

  this->_rooms[roomJid]->setSubject(subject);
}

bool QmlQXmppMucManager::setConfiguration(const QString& roomJid, const QVariantMap &form)
{
  if (!this->_rooms.contains(roomJid))
    return false;

  QXmppMucRoom* room = this->_rooms[roomJid];

  QXmppDataForm dataForm;
  dataForm.setType(QXmppDataForm::Submit);

  QList<QXmppDataForm::Field> fields;

  this->appendField(fields, "FORM_TYPE", "http://jabber.org/protocol/muc#roomconfig", QXmppDataForm::Field::HiddenField);
  Q_FOREACH(const QString& key, this->_fullConfigNameToShort.keys()) {
    const QString& shortKey(this->_fullConfigNameToShort[key]);

    this->appendField(fields, key, form.contains(shortKey) ? form[shortKey] : this->_defaultConfigValue[key], this->_configTypes[key]);
  }

  dataForm.setFields(fields);
  return room->setConfiguration(dataForm);
}

bool QmlQXmppMucManager::setPermission(const QString& roomJid, const QString jid, const QString affliation)
{
  if (!this->_rooms.contains(roomJid))
    return false;

  QXmppMucRoom* room = this->_rooms[roomJid];
  
  QXmppMucAdminIq iq;
  iq.setTo(roomJid);
  iq.setType(QXmppIq::Set);

  QList<QXmppMucItem> items;
  QXmppMucItem item;
  item.setAffiliation(QXmppMucItem::affiliationFromString(affliation));
  item.setJid(jid);
  items << item;

  iq.setItems(items);
  return this->_client->sendPacket(iq);
}

void QmlQXmppMucManager::onRoomAdded(QXmppMucRoom *room)
{
  SIGNAL_CONNECT_CHECK(QObject::connect(room, SIGNAL(destroyed(QObject*)),
    this, SLOT(onRoomDestroyed(QObject*))));

  SIGNAL_CONNECT_CHECK(QObject::connect(room, SIGNAL(created()),
    this, SLOT(onRoomCreated())));

  SIGNAL_CONNECT_CHECK(QObject::connect(room, SIGNAL(configurationReceived(const QXmppDataForm&)),
    this, SLOT(onConfigurationReceived(const QXmppDataForm&))));
  
  SIGNAL_CONNECT_CHECK(QObject::connect(room, SIGNAL(joined()),
    this, SLOT(onJoinedRoom())));

  SIGNAL_CONNECT_CHECK(QObject::connect(room, SIGNAL(kicked(const QString &, const QString &)),
    this, SLOT(onKicked(const QString &, const QString &))));

  SIGNAL_CONNECT_CHECK(QObject::connect(room, SIGNAL(left()),
    this, SLOT(onLeft())));

  SIGNAL_CONNECT_CHECK(QObject::connect(room, SIGNAL(nameChanged(const QString &)),
    this, SLOT(onNameChanged(const QString &))));

  SIGNAL_CONNECT_CHECK(QObject::connect(room, SIGNAL(messageReceived(const QXmppMessage &)),
    this, SLOT(onMessageReceived(const QXmppMessage &))));

  SIGNAL_CONNECT_CHECK(QObject::connect(room, SIGNAL(permissionsReceived(const QList<QXmppMucItem>&)),
    this, SLOT(onPermissionsReceived(const QList<QXmppMucItem>&))));

  SIGNAL_CONNECT_CHECK(QObject::connect(room, SIGNAL(participantAdded(const QString &)),
    this, SLOT(onParticipantAdded(const QString &))));
    
  SIGNAL_CONNECT_CHECK(QObject::connect(room, SIGNAL(participantChanged(const QString &)),
    this, SLOT(onParticipantChanged(const QString &))));
    
  SIGNAL_CONNECT_CHECK(QObject::connect(room, SIGNAL(participantRemoved(const QString &)),
    this, SLOT(onParticipantRemoved(const QString &))));

  SIGNAL_CONNECT_CHECK(QObject::connect(room, SIGNAL(participantPermissions(const QString &, const QXmppMucItem&)),
    this, SLOT(onParticipantPermissions(const QString &, const QXmppMucItem&))));
    
  this->_rooms[room->jid()] = room;

  emit this->roomAdded(room->jid());
}

void QmlQXmppMucManager::onRoomDestroyed(QObject *object)
{
  const QString key = this->_rooms.key(static_cast<QXmppMucRoom*>(object));
  this->_rooms.remove(key);
}

void QmlQXmppMucManager::onRoomCreated()
{
  QXmppMucRoom *room = qobject_cast<QXmppMucRoom *>(QObject::sender());
  if (!room)
    return;

  emit this->roomCreated(room->jid());
}

void QmlQXmppMucManager::onConfigurationReceived(const QXmppDataForm &configuration)
{
  QXmppMucRoom *room = qobject_cast<QXmppMucRoom *>(QObject::sender());
  if (!room)
    return;

  QVariantMap result;

  Q_FOREACH(const QXmppDataForm::Field &field, configuration.fields()) {
    const QString& key(field.key());
    if (!this->_fullConfigNameToShort.contains(key))
      continue;

    result[this->_fullConfigNameToShort[key]] = field.value();
  }

  emit this->configurationReceived(room->jid(), result);
}

void QmlQXmppMucManager::onJoinedRoom()
{
  QXmppMucRoom *room = qobject_cast<QXmppMucRoom *>(QObject::sender());
  if (!room)
    return;

  emit this->joined(room->jid());
}

void QmlQXmppMucManager::onKicked(const QString &jid, const QString &reason)
{
  QXmppMucRoom *room = qobject_cast<QXmppMucRoom *>(QObject::sender());
  if (!room)
    return;

  emit this->kicked(room->jid(), jid, reason);
}

void QmlQXmppMucManager::onLeft()
{
  QXmppMucRoom *room = qobject_cast<QXmppMucRoom *>(QObject::sender());
  if (!room)
    return;

  emit this->left(room->jid());
}

void QmlQXmppMucManager::onNameChanged(const QString &name)
{
  QXmppMucRoom *room = qobject_cast<QXmppMucRoom *>(QObject::sender());
  if (!room)
    return;

  emit this->nameChanged(room->jid(), name);
}

void QmlQXmppMucManager::onMessageReceived(const QXmppMessage &message)
{
  QXmppMucRoom *room = qobject_cast<QXmppMucRoom *>(QObject::sender());
  if (!room)
    return;

  QmlQXmppMessage qmlMessage(message);
  emit this->messageReceived(room->jid(), &qmlMessage);
}

void QmlQXmppMucManager::onPermissionsReceived(const QList<QXmppMucItem> &permissions)
{
  QXmppMucRoom *room = qobject_cast<QXmppMucRoom *>(QObject::sender());
  if (!room)
    return;

  QVariantList result;
  Q_FOREACH(const QXmppMucItem& item, permissions) {
    QVariantMap user;
    user["jid"] = item.jid();
    user["role"] = QXmppMucItem::roleToString(item.role());
    user["affiliation"] = QXmppMucItem::affiliationToString(item.affiliation());
    result.append(user);
  }

  emit this->permissionsReceived(room->jid(), result);
}

void QmlQXmppMucManager::onParticipantPermissions(const QString &jid, const QXmppMucItem& permissions)
{
  QXmppMucRoom *room = qobject_cast<QXmppMucRoom *>(QObject::sender());
  if (!room)
    return;

  QVariantMap user;
  user["jid"] = permissions.jid();
  user["role"] = QXmppMucItem::roleToString(permissions.role());
  user["affiliation"] = QXmppMucItem::affiliationToString(permissions.affiliation());
  emit this->participantPermissions(room->jid(), jid, user);
}

void QmlQXmppMucManager::onParticipantAdded(const QString &jid)
{
  QXmppMucRoom *room = qobject_cast<QXmppMucRoom *>(QObject::sender());
  if (!room)
    return;

  emit this->participantAdded(room->jid(), jid);
}

void QmlQXmppMucManager::onParticipantChanged(const QString &jid)
{
  QXmppMucRoom *room = qobject_cast<QXmppMucRoom *>(QObject::sender());
  if (!room)
    return;

  emit this->participantChanged(room->jid(), jid);
}

void QmlQXmppMucManager::onParticipantRemoved(const QString &jid)
{
  QXmppMucRoom *room = qobject_cast<QXmppMucRoom *>(QObject::sender());
  if (!room)
    return;

  emit this->participantRemoved(room->jid(), jid);
}

void QmlQXmppMucManager::appendField(QList<QXmppDataForm::Field> &fields, const QString& key, const QVariant& value, QXmppDataForm::Field::Type type)
{
  QXmppDataForm::Field field;
  field.setKey(key);
  field.setValue(value);
  field.setType(type);
  fields.append(field);
}

void QmlQXmppMucManager::initConfigMap()
{
  this->setShortConfig("muc#roomconfig_roomname", "name", QString(), QXmppDataForm::Field::TextSingleField);
  this->setShortConfig("muc#roomconfig_roomdesc", "description", QString(), QXmppDataForm::Field::TextSingleField);
  this->setShortConfig("muc#roomconfig_persistentroom", "persistent", true, QXmppDataForm::Field::BooleanField);
  this->setShortConfig("muc#roomconfig_publicroom", "public", false, QXmppDataForm::Field::BooleanField);
  this->setShortConfig("public_list", "public_list", true, QXmppDataForm::Field::BooleanField);
  this->setShortConfig("muc#roomconfig_passwordprotectedroom", "hasPassword", false, QXmppDataForm::Field::BooleanField);
  this->setShortConfig("muc#roomconfig_roomsecret", "password", QString(), QXmppDataForm::Field::TextPrivateField);
  this->setShortConfig("muc#roomconfig_maxusers", "maxusers", 200, QXmppDataForm::Field::ListSingleField);
  this->setShortConfig("muc#roomconfig_whois", "whois", QString("anyone"), QXmppDataForm::Field::ListSingleField);
  this->setShortConfig("muc#roomconfig_membersonly", "membersonly", true, QXmppDataForm::Field::BooleanField);
  this->setShortConfig("muc#roomconfig_moderatedroom", "moderated", true, QXmppDataForm::Field::BooleanField);
  this->setShortConfig("members_by_default", "membersByDefault", true, QXmppDataForm::Field::BooleanField);
  this->setShortConfig("muc#roomconfig_changesubject", "canChangeSubject", true, QXmppDataForm::Field::BooleanField);
  this->setShortConfig("allow_private_messages", "allowPrivateMessages", true, QXmppDataForm::Field::BooleanField);
  this->setShortConfig("allow_private_messages_from_visitors", "allowPrivateMessagesFromVisitors", QString("anyone"), QXmppDataForm::Field::ListSingleField);
  this->setShortConfig("allow_query_users", "allowQueryUsers", true, QXmppDataForm::Field::BooleanField);
  this->setShortConfig("muc#roomconfig_allowinvites", "allowInvites", true, QXmppDataForm::Field::BooleanField);
  this->setShortConfig("muc#roomconfig_allowvisitorstatus", "allowVisitorStatus", true, QXmppDataForm::Field::BooleanField);
  this->setShortConfig("muc#roomconfig_allowvisitornickchange", "allowVisitorNickChange", false, QXmppDataForm::Field::BooleanField);
  this->setShortConfig("muc#roomconfig_allowvoicerequests", "allowVoiceRequests", false, QXmppDataForm::Field::BooleanField);
  this->setShortConfig("muc#roomconfig_voicerequestmininterval", "voiceRequestMinInterval", 1800, QXmppDataForm::Field::TextSingleField);
  this->setShortConfig("muc#roomconfig_captcha_whitelist", "captchaWhitelist", QStringList(), QXmppDataForm::Field::JidMultiField);
}

void QmlQXmppMucManager::setShortConfig(const QString& fullName, const QString& shortName, const QVariant& defaultValue, QXmppDataForm::Field::Type type)
{
  this->_fullConfigNameToShort[fullName] = shortName;
  this->_defaultConfigValue[fullName] = defaultValue;
  this->_configTypes[fullName] = type;
}

