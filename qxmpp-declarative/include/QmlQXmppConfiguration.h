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

#include <QtCore/QObject>

class QXmppConfiguration;

class QmlQXmppConfiguration : public QObject
{
  Q_OBJECT
  Q_PROPERTY(QString host READ host WRITE setHost);
  Q_PROPERTY(QString domain READ domain WRITE setDomain);
  Q_PROPERTY(int port READ port WRITE setPort);
  Q_PROPERTY(QString user READ user WRITE setUser);
  Q_PROPERTY(QString password READ password WRITE setPassword);
  Q_PROPERTY(QString resource READ resource WRITE setResource);
  Q_PROPERTY(QString jid READ jid WRITE setJid);
  Q_PROPERTY(bool autoAcceptSubscriptions READ autoAcceptSubscriptions WRITE setAutoAcceptSubscriptions);
  Q_PROPERTY(bool autoReconnectionEnabled READ autoReconnectionEnabled WRITE setAutoReconnectionEnabled);
  Q_PROPERTY(int keepAliveInterval READ keepAliveInterval WRITE setKeepAliveInterval);
  Q_PROPERTY(int keepAliveTimeout READ keepAliveTimeout WRITE setKeepAliveTimeout);
  Q_PROPERTY(int streamManagementMode READ streamManagementMode WRITE setStreamManagementMode);

public:
  QmlQXmppConfiguration(QXmppConfiguration *configuration, QObject *parent = 0);
  ~QmlQXmppConfiguration();

  QString host() const;
  void setHost(const QString&);

  QString domain() const;
  void setDomain(const QString&);

  int port() const;
  void setPort(int);

  QString user() const;
  void setUser(const QString&);

  QString password() const;
  void setPassword(const QString&);

  QString resource() const;
  void setResource(const QString&);

  QString jid() const;
  void setJid(const QString &jid);

  bool autoAcceptSubscriptions() const;
  void setAutoAcceptSubscriptions(bool);

  bool autoReconnectionEnabled() const;
  void setAutoReconnectionEnabled(bool);

  int keepAliveInterval() const;
  void setKeepAliveInterval(int secs);

  int keepAliveTimeout() const;
  void setKeepAliveTimeout(int secs);

  int streamManagementMode() const;
  void setStreamManagementMode(int mode);

private:
  QXmppConfiguration *_xmppConfiguration;
};