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

#include <QtCore/QCoreApplication>

#include <QXmppLogger.h>

#include <QmlQXmppMessage.h>
#include <QmlQXmppPlugin.h>
#include <QmlQXmppPresence.h>
#include <QmlQXmppVCard.h>
#include <QmlQXmppLastActivity.h>
#include <QmlQXmppClient.h>
#include <QmlQXmppConfiguration.h>
#include <QmlQXmppArchiveManager.h>
#include <QmlQXmppRosterManager.h>
#include <QmlQXmppVCardManager.h>
#include <QmlQXmppLastActivityManager.h>
#include <QmlQXmppPEPManager.h>
#include <QmlQXmppGaming.h>
#include <QmlQXmppMucManager.h>
#include <QmlQXmppDiscoveryManager.h>
#include <QmlQXmppDiscovery.h>
#include <QmlQXmppBookmarkManager.h>
#include <QmlQXmppLogger.h>
#include <QmlQXmppUserBlacklistManager.h>

void QmlQXmppPlugin::registerTypes(const char *uri)
{
  qmlRegisterType<QmlQXmppClient>("QXmpp", 1, 0, "QXmppClient");
  qmlRegisterType<QmlQXmppDiscovery>("QXmpp", 1, 0, "QmlQXmppDiscovery");
  qmlRegisterType<QmlQXmppVCard>("QXmpp", 1, 0, "QXmppVCard");
  qmlRegisterType<QmlQXmppMessage>("QXmpp", 1, 0, "QXmppMessage");
  qmlRegisterType<QmlQXmppLastActivity>("QXmpp", 1, 0, "QmlQXmppLastActivity");
  qmlRegisterType<QmlQXmppGaming>("QXmpp", 1, 0, "QXmppGaming");

  qmlRegisterUncreatableType<QmlQXmppPresence>("QXmpp", 1, 0, "QXmppPresence", "Do not create QXmppPresence instances.");
  qmlRegisterUncreatableType<QmlQXmppConfiguration>("QXmpp", 1, 0, "QXmppConfiguration", "Do not create QXmppConfiguration instances.");
  qmlRegisterUncreatableType<QmlQXmppArchiveManager>("QXmpp", 1, 0, "QXmppArchiveManager", "Do not create QXmppArchiveManager instances.");
  qmlRegisterUncreatableType<QmlQXmppRosterManager>("QXmpp", 1, 0, "QXmppRosterManager", "Do not create QXmppRosterManager instances.");
  qmlRegisterUncreatableType<QmlQXmppVCardManager>("QXmpp", 1, 0, "QXmppVCardManager", "Do not create QXmppVCardManager instances.");
  qmlRegisterUncreatableType<QmlQXmppLastActivityManager>("QXmpp", 1, 0, "QXmppLastActivityManager", "Do not create QXmppLastActivityManager instances.");
  qmlRegisterUncreatableType<QmlQXmppPEPManager>("QXmpp", 1, 0, "QmlQXmppPEPManager", "Do not create QmlQXmppPEPManager instances.");
  qmlRegisterUncreatableType<QmlQXmppMucManager>("QXmpp", 1, 0, "QmlQXmppMucManager", "Do not create QmlQXmppMucManager instances.");
  qmlRegisterUncreatableType<QmlQXmppDiscoveryManager>("QXmpp", 1, 0, "QmlQXmppDiscoveryManager", "Do not create QmlQXmppDiscoveryManager instances.");
  qmlRegisterUncreatableType<QmlQXmppBookmarkManager>("QXmpp", 1, 0, "QmlQXmppBookmarkManager", "Do not create QmlQXmppBookmarkManager instances.");
  qmlRegisterUncreatableType<QmlQXmppLogger>("QXmpp", 1, 0, "QmlQXmppLogger", "Do not create QmlQXmppLogger instances.");
  qmlRegisterUncreatableType<QmlQXmppUserBlacklistManager>("QXmpp", 1, 0, "QmlQXmppUserBlacklistManager", "Do not create QmlQXmppUserBlacklistManager instances.");

  qmlRegisterType<QXmppLogger>("QXmpp", 1, 0, "QXmppLogger");
}

void QmlQXmppPlugin::initializeEngine(QQmlEngine *engine, const char *uri)
{

}
