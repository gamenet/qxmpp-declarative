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

#include <QXmppArchiveIq.h>
#include <QXmppArchiveManager.h>
#include <QmlQXmppArchiveManager.h>

#include <QDebug>

#define SIGNAL_CONNECT_CHECK(X) { bool result = X; Q_ASSERT_X(result, __FUNCTION__ , #X); }

QmlQXmppArchiveManager::QmlQXmppArchiveManager(QObject *parent)
{
  
}

QmlQXmppArchiveManager::~QmlQXmppArchiveManager()
{

}

void QmlQXmppArchiveManager::archiveListReceived(const QList<QXmppArchiveChat> &chats, const QXmppResultSetReply &rsmReply)
{

}

void QmlQXmppArchiveManager::archiveChatReceived(const QXmppArchiveChat &chat, const QXmppResultSetReply &rsmReply)
{


}

void QmlQXmppArchiveManager::connectSignals()
{
  Q_ASSERT(_archieveManager);

  SIGNAL_CONNECT_CHECK(connect(_archieveManager, SIGNAL(archiveChatReceived(QXmppArchiveChat, QXmppResultSetReply)), this,
    SLOT(archiveChatReceived(QXmppArchiveChat, QXmppResultSetReply))));
  SIGNAL_CONNECT_CHECK(connect(_archieveManager, SIGNAL(archiveListReceived(QList<QXmppArchiveChat>, QXmppResultSetReply)), this,
    SLOT(archiveListReceived(QList<QXmppArchiveChat>, QXmppResultSetReply))));
}