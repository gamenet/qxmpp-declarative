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
  QString description() const;
  QString email() const;
  QString firstName() const;
  QString fullName() const;
  QString lastName() const;
  QString middleName() const;
  QString nickName() const;
  QString url() const;

private:
  QXmppVCardIq _vcard;
};
