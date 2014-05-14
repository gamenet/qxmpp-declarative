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

#include <QXmppVCardIq.h>
#include <QDomElement>
#include <QVariant>

class QmlQXmppVCard : public QObject, public QXmppVCardIq
{
  Q_OBJECT
  Q_PROPERTY(QString from READ from WRITE setFrom)
  Q_PROPERTY(QDate birthday READ birthday WRITE setBirthday);
  Q_PROPERTY(QString description READ description WRITE setDescription);
  Q_PROPERTY(QString email READ email WRITE setEmail);
  Q_PROPERTY(QString firstName READ firstName WRITE setFirstName);
  Q_PROPERTY(QString fullName READ fullName WRITE setFullName);
  Q_PROPERTY(QString lastName READ lastName WRITE setLastName);
  Q_PROPERTY(QString middleName READ middleName WRITE setMiddleName);
  Q_PROPERTY(QString nickName READ nickName WRITE setNickName);
  Q_PROPERTY(QString url READ url WRITE setUrl);
  Q_PROPERTY(QVariantMap extra READ extra WRITE setExtra)

public:
  QmlQXmppVCard(const QString &elementName = QString("EXTRA"));
  QmlQXmppVCard(const QmlQXmppVCard &p);
  ~QmlQXmppVCard();

  QmlQXmppVCard& operator=(const QmlQXmppVCard &xmppVCard);

  void setExtra(const QVariantMap &map);
  QVariantMap extra() const;

  void setExtraElementName(const QString &elementName);
  QString extraElementName() const;

protected:
  void parseElementFromChild(const QDomElement&);
  void toXmlElementFromChild(QXmlStreamWriter *writer) const;

private:
  QString _extraElementName;
  QVariantMap _extraData;
};