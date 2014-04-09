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

#include <QtDeclarative/QDeclarativeListProperty>

#include <QXmppVCardIq.h>

class QmlQXmppVCard : public QObject
{
  Q_OBJECT
  Q_PROPERTY(QString from READ from)
  Q_PROPERTY(QDate birthday READ birthday);
  Q_PROPERTY(QString description READ description);
  Q_PROPERTY(QString email READ email);
  Q_PROPERTY(QString firstName READ firstName);
  Q_PROPERTY(QString fullName READ fullName);
  Q_PROPERTY(QString lastName READ lastName);
  Q_PROPERTY(QString middleName READ middleName);
  Q_PROPERTY(QString nickName READ middleName);
  Q_PROPERTY(QString url READ url);

public:
  QmlQXmppVCard(QObject *parent = 0);
  ~QmlQXmppVCard();

  QmlQXmppVCard& operator=(const QXmppVCardIq &xmppVCard);

  QString from() const;
  
  QDate birthday() const;
  //void setBirthday(const QDate &value);

  QString description() const;
  //void setDescription(const QString &value);

  QString email() const;
  //void setEmail(const QString &value);

  QString firstName() const;
  //void setFirstName(const QString &value);

  QString fullName() const;
  //void setFullName(const QString &value);;

  QString lastName() const;
  //void setLastName(const QString &value);;

  QString middleName() const;
  //void setMiddleName(const QString &value);

  QString nickName() const;
  //void setNickName(const QString &value);

  QString url() const;
  //void setUrl(const QString &value);

private:
  QXmppVCardIq _vcard;
};
