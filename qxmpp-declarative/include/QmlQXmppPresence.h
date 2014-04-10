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

class QmlQXmppPresence : public QObject
{
  Q_OBJECT
  Q_PROPERTY(QString from READ from);
  Q_PROPERTY(QString type READ type WRITE setType);
  Q_PROPERTY(QString status READ statusText WRITE setStatusText);

public:
  QmlQXmppPresence(const QXmppPresence &xmppPresence, QObject *parent = 0);
  ~QmlQXmppPresence();

  QString from() const;

  QString type() const;
  void setType(const QString &value);

  QString statusText() const;
  void setStatusText(const QString &value);

  static QString statusToString(QXmppPresence::AvailableStatusType type);
  static QXmppPresence::AvailableStatusType stringToStatus(const QString& str);

private:
  QXmppPresence _presence;
};
