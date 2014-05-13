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
#include <QtDeclarative/QDeclarative.h>
#include <QtDeclarative/QDeclarativeEngine>

#include <QXmppLogger.h>

#include <QmlQXmppPlugin.h>
#include <QmlQXmppPresence.h>
#include <QmlQXmppClient.h>
#include <QmlQXmppConfiguration.h>
#include <QmlQXmppArchiveManager.h>
#include <QmlQXmppRosterManager.h>
#include <QmlQXmppVCardManager.h>
#include <QmlQXmppVCard.h>

void QmlQXmppPlugin::registerTypes(const char *uri)
{
  qmlRegisterType<QmlQXmppVCard>("QXmpp", 1, 0, "QXmppVCardEx");
  qmlRegisterUncreatableType<QmlQXmppPresence>("QXmpp", 1, 0, "QXmppPresence", "Do not create QXmppPresence instances.");
  qmlRegisterType<QmlQXmppClient>("QXmpp", 1, 0, "QXmppClient");
  qmlRegisterUncreatableType<QmlQXmppConfiguration>("QXmpp", 1, 0, "QXmppConfiguration", "Do not create QXmppConfiguration instances.");
  qmlRegisterUncreatableType<QmlQXmppArchiveManager>("QXmpp", 1, 0, "QXmppArchiveManager", "Do not create QXmppArchiveManager instances.");
  qmlRegisterUncreatableType<QmlQXmppRosterManager>("QXmpp", 1, 0, "QXmppRosterManager", "Do not create QXmppRosterManager instances.");
  qmlRegisterUncreatableType<QmlQXmppVCardManager>("QXmpp", 1, 0, "QXmppVCardManager", "Do not create QmlQXmppVCardManager instances.");
  qmlRegisterType<QmlQXmppVCard>("QXmpp", 1, 0, "QXmppVCard");
  qmlRegisterType<QXmppLogger>("QXmpp", 1, 0, "QXmppLogger");
}

void QmlQXmppPlugin::initializeEngine(QDeclarativeEngine *engine, const char *uri)
{

}
