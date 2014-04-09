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

#include <QtCore/QList>
#include <QtCore/QSharedPointer>

#include <QXmppVCardManager.h>
#include <QmlQXmppVCard.h>

class QmlQXmppVCardManager : public QObject
{
  Q_OBJECT

public:
  QmlQXmppVCardManager(QXmppVCardManager *vcardMgr = 0, QObject * = 0);
  ~QmlQXmppVCardManager();

public slots:
  void requestVCard(const QString& jid);

private slots:
  void onVCardReceived(const QXmppVCardIq& vcardIq); 

signals:
  void vCardReceived(QmlQXmppVCard *vcard);

private:
  void connectSignals();

private:
  QXmppVCardManager *_vcardManager;
};
