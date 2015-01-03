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

#include <QmlQXmppConfiguration.h>

#include <QXmppConfiguration.h>

QmlQXmppConfiguration::QmlQXmppConfiguration(QXmppConfiguration *configuration, QObject *parent)
  : QObject(parent)
  , _xmppConfiguration(configuration)
{
}

QmlQXmppConfiguration::~QmlQXmppConfiguration()
{

}

QString QmlQXmppConfiguration::host() const
{
  Q_ASSERT(this->_xmppConfiguration);

  return this->_xmppConfiguration->host();
}

void QmlQXmppConfiguration::setHost(const QString& value)
{
  Q_ASSERT(this->_xmppConfiguration);

  this->_xmppConfiguration->setHost(value);
}

QString QmlQXmppConfiguration::domain() const
{
  Q_ASSERT(this->_xmppConfiguration);

  return this->_xmppConfiguration->domain();
}

void QmlQXmppConfiguration::setDomain(const QString& value)
{
  Q_ASSERT(this->_xmppConfiguration);

  this->_xmppConfiguration->setDomain(value);
}

int QmlQXmppConfiguration::port() const
{
  Q_ASSERT(this->_xmppConfiguration);

  return this->_xmppConfiguration->port();
}

void QmlQXmppConfiguration::setPort(int value)
{
  Q_ASSERT(this->_xmppConfiguration);

  this->_xmppConfiguration->setPort(value);
}

QString QmlQXmppConfiguration::user() const
{
  Q_ASSERT(this->_xmppConfiguration);

  return this->_xmppConfiguration->user();
}

void QmlQXmppConfiguration::setUser(const QString& value)
{
  Q_ASSERT(this->_xmppConfiguration);

  this->_xmppConfiguration->setUser(value);
}

QString QmlQXmppConfiguration::password() const
{
  Q_ASSERT(this->_xmppConfiguration);

  return this->_xmppConfiguration->password();
}

void QmlQXmppConfiguration::setPassword(const QString& value)
{
  Q_ASSERT(this->_xmppConfiguration);

  this->_xmppConfiguration->setPassword(value);
}

QString QmlQXmppConfiguration::resource() const
{
  Q_ASSERT(this->_xmppConfiguration);

  return this->_xmppConfiguration->resource();
}

void QmlQXmppConfiguration::setResource(const QString& value)
{
  Q_ASSERT(this->_xmppConfiguration);

  this->_xmppConfiguration->setResource(value);
}

QString QmlQXmppConfiguration::jid() const
{
  Q_ASSERT(this->_xmppConfiguration);

  return this->_xmppConfiguration->jid();
}

void QmlQXmppConfiguration::setJid(const QString &value)
{
  Q_ASSERT(this->_xmppConfiguration);

  this->_xmppConfiguration->setJid(value);
}

bool QmlQXmppConfiguration::autoAcceptSubscriptions() const
{
  Q_ASSERT(this->_xmppConfiguration);
  
  return this->_xmppConfiguration->autoAcceptSubscriptions();
}

void QmlQXmppConfiguration::setAutoAcceptSubscriptions(bool value)
{
  Q_ASSERT(this->_xmppConfiguration);

  this->_xmppConfiguration->setAutoAcceptSubscriptions(value);
}

bool QmlQXmppConfiguration::autoReconnectionEnabled() const
{
  Q_ASSERT(this->_xmppConfiguration);

  return this->_xmppConfiguration->autoReconnectionEnabled();
}

void QmlQXmppConfiguration::setAutoReconnectionEnabled(bool value)
{
  Q_ASSERT(this->_xmppConfiguration);

  this->_xmppConfiguration->setAutoReconnectionEnabled(value);
}

int QmlQXmppConfiguration::keepAliveInterval() const
{
  Q_ASSERT(this->_xmppConfiguration);

  return this->_xmppConfiguration->keepAliveInterval();
}

void QmlQXmppConfiguration::setKeepAliveInterval(int value)
{
  Q_ASSERT(this->_xmppConfiguration);

  this->_xmppConfiguration->setKeepAliveInterval(value);
}

int QmlQXmppConfiguration::keepAliveTimeout() const
{
  Q_ASSERT(this->_xmppConfiguration);

  return this->_xmppConfiguration->keepAliveTimeout();
}

void QmlQXmppConfiguration::setKeepAliveTimeout(int value)
{
  Q_ASSERT(this->_xmppConfiguration);

  this->_xmppConfiguration->setKeepAliveTimeout(value);
}