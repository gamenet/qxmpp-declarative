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

#include <QmlQXmppPresence.h>

QmlQXmppPresence::QmlQXmppPresence(const QXmppPresence &xmppPresence, QObject *parent)
  : _presence(xmppPresence)
  , QObject(parent)
{
}

QmlQXmppPresence::~QmlQXmppPresence()
{
}

QString QmlQXmppPresence::from() const
{
  return this->_presence.from();
}

QString QmlQXmppPresence::type() const
{
  if (QXmppPresence::Available == this->_presence.type()) {
    return statusToString(this->_presence.availableStatusType());
  } else {
    return "offline";
  }
}

void QmlQXmppPresence::setType(const QString& value)
{
  if ("offline" == value) {
    this->_presence.setType(QXmppPresence::Unavailable);
  } else {
    this->_presence.setAvailableStatusType(stringToStatus(value));
  }
}

QString QmlQXmppPresence::statusText() const
{
  return this->_presence.statusText();
}

void QmlQXmppPresence::setStatusText(const QString &value)
{
  this->_presence.setStatusText(value);
}

QString QmlQXmppPresence::statusToString(QXmppPresence::AvailableStatusType value)
{
  QString result;
  switch (value) {
  case QXmppPresence::Online:
    result = "online";
    break;
  case QXmppPresence::Away:
    result = "away";
    break;
  case QXmppPresence::XA:
    result = "xa";
    break;
  case QXmppPresence::DND:
    result = "dnd";
    break;
  case QXmppPresence::Chat:
    result = "chat";
    break;
  }
  return result;
}

QXmppPresence::AvailableStatusType QmlQXmppPresence::stringToStatus(const QString& value)
{
  if (value == "online") {
    return QXmppPresence::Online;
  } else if (value == "away") {
    return QXmppPresence::Away;
  } else if (value == "xa") {
    return QXmppPresence::XA;
  } else if (value == "dnd") {
    return QXmppPresence::DND;
  } else if (value == "chat") {
    return QXmppPresence::Chat;
  }
  return QXmppPresence::Online;
}