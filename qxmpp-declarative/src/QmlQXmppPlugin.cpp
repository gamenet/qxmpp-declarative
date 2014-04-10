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

#include <QtCore/QCoreApplication>
#include <QtCore/QDebug>
#include <QtDeclarative/QDeclarative.h>
#include <QtDeclarative/QDeclarativeEngine>

#include <QXmppLogger.h>

#include <QmlQXmppPlugin.h>
#include <QmlQXmppPresence.h>
#include <QmlQXmppClient.h>
#include <QmlQXmppArchiveManager.h>
#include <QmlQXmppRosterManager.h>
#include <QmlQXmppVCardManager.h>
#include <VCardPhotoProvider.h>

void QmlQXmppPlugin::registerTypes(const char *uri)
{
  qmlRegisterUncreatableType<QmlQXmppPresence>("QXmpp", 1, 0, "QXmppPresence", "Do not create QXmppPresence instances.");
  qmlRegisterType<QmlQXmppClient>("QXmpp", 1, 0, "QXmppClient");
  qmlRegisterUncreatableType<QmlQXmppArchiveManager>("QXmpp", 1, 0, "QXmppArchiveManager", "Do not create QXmppArchiveManager instances.");
  qmlRegisterUncreatableType<QmlQXmppRosterManager>("QXmpp", 1, 0, "QXmppRosterManager", "Do not create QXmppRosterManager instances.");
  qmlRegisterUncreatableType<QmlQXmppVCardManager>("QXmpp", 1, 0, "QXmppVCardManager", "Do not create QmlQXmppVCardManager instances.");
  qmlRegisterType<QmlQXmppVCard>("QXmpp", 1, 0, "QXmppVCard");
  qmlRegisterType<QXmppLogger>("QXmpp", 1, 0, "QXmppLogger");
}

void QmlQXmppPlugin::initializeEngine(QDeclarativeEngine *engine, const char *uri)
{
  engine->addImageProvider("vcard", new VCardPhotoProvider);
}

#ifdef _DEBUG
Q_EXPORT_PLUGIN2(qxmpp-declaratived, QmlQXmppPlugin);
#else
Q_EXPORT_PLUGIN2(qxmpp-declarative, QmlQXmppPlugin);
#endif