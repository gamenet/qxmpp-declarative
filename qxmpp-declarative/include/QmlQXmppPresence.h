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

#pragma once

#include <QtCore/QObject>
#include <QXmppPresence.h>

class QmlQXmppPresence : public QObject, public QXmppPresence
{
  Q_OBJECT
  Q_ENUMS(StatusType)
  Q_PROPERTY(StatusType type READ type);
  Q_PROPERTY(QString status READ statusText);

public:
  enum StatusType {
    Online = QXmppPresence::Online,
    Away = QXmppPresence::Away,
    XA = QXmppPresence::XA,
    DND = QXmppPresence::DND,
    Chat = QXmppPresence::Chat,
    Invisible = QXmppPresence::Invisible
  };

  //QmlQXmppPresence(QObject *parent = 0);
  QmlQXmppPresence(const QXmppPresence &xmppPresence, QObject *parent = 0);
  ~QmlQXmppPresence();

  QmlQXmppPresence& operator=(const QXmppPresence &msg);

  QmlQXmppPresence::StatusType type() const;
  //QString status() const;
private:
  QXmppPresence _presence;
};
