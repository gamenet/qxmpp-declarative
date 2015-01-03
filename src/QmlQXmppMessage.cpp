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

#include <QmlQXmppMessage.h>

QmlQXmppMessage::QmlQXmppMessage(QObject *parent)
    : QObject(parent)
{
}

QmlQXmppMessage::QmlQXmppMessage(const QXmppMessage &other, QObject *parent)
    : QObject(parent), _message(other)
{
}

QmlQXmppMessage::~QmlQXmppMessage()
{

}

QmlQXmppMessage& QmlQXmppMessage::operator=(const QXmppMessage &other) {
    this->_message = other;
    return *this;
}

QString QmlQXmppMessage::body() const
{
    return this->_message.body();
}

bool QmlQXmppMessage::isAttentionRequested() const
{
    return this->_message.isAttentionRequested();
}

bool QmlQXmppMessage::isReceiptRequested() const
{
    return this->_message.isReceiptRequested();
}

QString QmlQXmppMessage::mucInvitationJid() const
{
    return this->_message.mucInvitationJid();
}

QString QmlQXmppMessage::mucInvitationPassword() const
{
    return this->_message.mucInvitationPassword();
}

QString QmlQXmppMessage::mucInvitationReason() const
{
    return this->_message.mucInvitationReason();
}

QString QmlQXmppMessage::receiptId() const
{
    return this->_message.receiptId();
}

QDateTime QmlQXmppMessage::stamp() const
{
    return this->_message.stamp();
}

QmlQXmppMessage::State QmlQXmppMessage::state() const
{
    return static_cast<QmlQXmppMessage::State>(this->_message.state());
}

QString QmlQXmppMessage::xhtml() const
{
    return this->_message.xhtml();
}

QmlQXmppMessage::Type QmlQXmppMessage::type() const
{
    return static_cast<QmlQXmppMessage::Type>(this->_message.type());
}

QString QmlQXmppMessage::subject() const
{
    return this->_message.subject();
}

QString QmlQXmppMessage::thread() const
{
    return this->_message.thread();
}

QString QmlQXmppMessage::to() const
{
    return this->_message.to();
}

QString QmlQXmppMessage::from() const
{
    return this->_message.from();
}

QString QmlQXmppMessage::id() const
{
    return this->_message.id();
}

QString QmlQXmppMessage::lang() const
{
    return this->_message.lang();
}

QXmppStanza::Error QmlQXmppMessage::error() const
{
    return this->_message.error();
}

QXmppMessage::Type QmlQXmppMessage::parseMessageType(int type) {
  switch (type) {
  case QXmppMessage::Error:
    return QXmppMessage::Error;
  case QXmppMessage::Normal:
    return QXmppMessage::Normal;
  case QXmppMessage::Chat:
    return QXmppMessage::Chat;
  case QXmppMessage::GroupChat:
    return QXmppMessage::GroupChat;
  case QXmppMessage::Headline:
    return QXmppMessage::Headline;
  default:
    return QXmppMessage::Error;
  };
}

QXmppMessage::State QmlQXmppMessage::parseMessageState(int state) {
  switch (state) {
  case QXmppMessage::None:
    return QXmppMessage::None;
  case QXmppMessage::Active:
    return QXmppMessage::Active;
  case QXmppMessage::Inactive:
    return QXmppMessage::Inactive;
  case QXmppMessage::Gone:
    return QXmppMessage::Gone;
  case QXmppMessage::Composing:
    return QXmppMessage::Composing;
  case QXmppMessage::Paused:
    return QXmppMessage::Paused;
  default:
    return QXmppMessage::None;
  }
}

