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

#include <QmlQXmppPresence.h>

QmlQXmppPresence::QmlQXmppPresence(const QXmppPresence &xmppPresence, QObject *parent)
  : _presence(xmppPresence)
  , QObject(parent)
{
}

QmlQXmppPresence::~QmlQXmppPresence()
{
}

QString QmlQXmppPresence::from() const
{
  return _presence.from();
}

QString QmlQXmppPresence::type() const
{
  if (QXmppPresence::Available == _presence.type()) {
    return statusToString(_presence.availableStatusType());
  } else {
    return "offline";
  }
}

void QmlQXmppPresence::setType(const QString& value)
{
  if ("offline" == value) {
    _presence.setType(QXmppPresence::Unavailable);
  } else {
    _presence.setAvailableStatusType(stringToStatus(value));
  }
}

QString QmlQXmppPresence::statusText() const
{
  return _presence.statusText();
}

void QmlQXmppPresence::setStatusText(const QString &value)
{
  _presence.setStatusText(value);
}

QString QmlQXmppPresence::statusToString(QXmppPresence::AvailableStatusType value)
{
  QString result;
  switch (value) {
  case QXmppPresence::Online:
    result = "online";
    break;
  case QXmppPresence::Away:
    result = "away";
    break;
  case QXmppPresence::XA:
    result = "xa";
    break;
  case QXmppPresence::DND:
    result = "dnd";
    break;
  case QXmppPresence::Chat:
    result = "chat";
    break;
  }
  return result;
}

QXmppPresence::AvailableStatusType QmlQXmppPresence::stringToStatus(const QString& value)
{
  if (value == "online") {
    return QXmppPresence::Online;
  } else if (value == "away") {
    return QXmppPresence::Away;
  } else if (value == "xa") {
    return QXmppPresence::XA;
  } else if (value == "dnd") {
    return QXmppPresence::DND;
  } else if (value == "chat") {
    return QXmppPresence::Chat;
  }
  return QXmppPresence::Online;
}