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
#include <QXmppArchiveIq.h>
#include <QXmppArchiveManager.h>
#include <QmlQXmppArchiveManager.h>

QmlQXmppArchiveManager::QmlQXmppArchiveManager(QXmppArchiveManager *archiveMgr, QObject *parent)
  : QObject(parent)
  , _archieveManager(archiveMgr)
{
  this->connectSignals();
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
  Q_ASSERT(this->_archieveManager);

  SIGNAL_CONNECT_CHECK(connect(this->_archieveManager, SIGNAL(archiveChatReceived(QXmppArchiveChat, QXmppResultSetReply)), this,
    SLOT(archiveChatReceived(QXmppArchiveChat, QXmppResultSetReply))));
  SIGNAL_CONNECT_CHECK(connect(this->_archieveManager, SIGNAL(archiveListReceived(QList<QXmppArchiveChat>, QXmppResultSetReply)), this,
    SLOT(archiveListReceived(QList<QXmppArchiveChat>, QXmppResultSetReply))));
}