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

#include <QmlQXmppVCard.h>

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
