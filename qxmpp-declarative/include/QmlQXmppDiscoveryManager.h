/*
 * The MIT License (MIT)
 * 
 * Copyright (c) 2015 GameNet
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

class QmlQXmppDiscovery;
class QXmppDiscoveryManager;
class QXmppDiscoveryIq;

class QmlQXmppDiscoveryManager : public QObject
{
  Q_OBJECT
public:
  QmlQXmppDiscoveryManager(QXmppDiscoveryManager *manager, QObject *parent = 0);
  virtual ~QmlQXmppDiscoveryManager();

public slots:
  QString requestInfo(const QString& jid, const QString& node = QString());
  QString requestItems(const QString& jid, const QString& node = QString());

signals:
  /// This signal is emitted when an information response is received.
  void infoReceived(QmlQXmppDiscovery* info);

  /// This signal is emitted when an items response is received.
  void itemsReceived(QmlQXmppDiscovery* items);

private slots:
  void onInfoReceived(const QXmppDiscoveryIq& info);
  void onItemsReceived(const QXmppDiscoveryIq& items);

private:
  QXmppDiscoveryManager *_manager;
};

