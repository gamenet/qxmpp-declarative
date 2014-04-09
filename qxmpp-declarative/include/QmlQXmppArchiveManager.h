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

class QXmppArchiveChat;
class QXmppArchiveManager;
class QXmppResultSetReply;

class QmlQXmppArchiveManager : public QObject
{
  Q_OBJECT
public:
  QmlQXmppArchiveManager(QObject *parent = 0);
  ~QmlQXmppArchiveManager();

private slots:
  void archiveListReceived(const QList<QXmppArchiveChat> &chats, const QXmppResultSetReply &rsmReply);
  void archiveChatReceived(const QXmppArchiveChat &chat, const QXmppResultSetReply &rsmReply);

private:
  void connectSignals();

private:
  QXmppArchiveManager* _archieveManager;
};