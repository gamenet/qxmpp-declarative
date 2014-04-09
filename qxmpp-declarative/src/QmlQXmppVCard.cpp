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

#include <QmlQXmppVCard.h>

//#include <AvatarCache.h>

QmlQXmppVCard::QmlQXmppVCard(QObject *parent)
    : QObject(parent)
{
}

QmlQXmppVCard::~QmlQXmppVCard()
{
}

QmlQXmppVCard& QmlQXmppVCard::operator=(const QXmppVCardIq &xmppVCard)
{
  this->_vcard = xmppVCard;
  return *this;
}

QString QmlQXmppVCard::from() const
{
  return _vcard.from();
}

QDate QmlQXmppVCard::birthday() const
{
    return _vcard.birthday();
}

QString QmlQXmppVCard::description() const
{
    return _vcard.description();
}

QString QmlQXmppVCard::email() const
{
    return _vcard.email();
}

QString QmlQXmppVCard::firstName() const
{
    return _vcard.firstName();
}

QString QmlQXmppVCard::fullName() const
{
    return _vcard.fullName();
}

QString QmlQXmppVCard::lastName() const
{
    return _vcard.lastName();
}

QString QmlQXmppVCard::middleName() const
{
    return _vcard.middleName();
}

QString QmlQXmppVCard::nickName() const
{
    return _vcard.nickName();
}

QString QmlQXmppVCard::url() const
{
    return _vcard.url();
}
