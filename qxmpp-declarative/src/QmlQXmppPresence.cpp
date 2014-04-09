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
  : QXmppPresence(xmppPresence)
  , QObject(parent)
{

}

QmlQXmppPresence::~QmlQXmppPresence()
{
}

QmlQXmppPresence& QmlQXmppPresence::operator=(const QXmppPresence &msg)
{
  this->_presence = msg;
  return *this;
}

QmlQXmppPresence::StatusType QmlQXmppPresence::type() const
{
  return StatusType(availableStatusType());
}
//
//QString QmlQXmppPresence::status() const
//{
//  return statusText()
//}