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
#include <QtCore/QStringList>
#include <QtCore/QVariantList>
#include <QtCore/QVariantMap>

class QXmppDiscoveryIq;
class QXmppDataForm;

class QmlQXmppDiscovery : public QObject
{
  Q_OBJECT
  Q_PROPERTY(QString id READ id);
  Q_PROPERTY(QStringList features READ features);
  Q_PROPERTY(QVariantList identities READ identities);
  Q_PROPERTY(QVariantList items READ items);
  Q_PROPERTY(QString queryNode READ queryNode);
  Q_PROPERTY(QString queryType READ queryType);

  Q_PROPERTY(QVariantMap form READ form);

public:
  QmlQXmppDiscovery();
  QmlQXmppDiscovery(const QXmppDiscoveryIq *discovery, QObject* parent = 0);
  QmlQXmppDiscovery(const QmlQXmppDiscovery &p);
  virtual ~QmlQXmppDiscovery();

  QmlQXmppDiscovery& operator=(const QmlQXmppDiscovery &rhs);

  QString id() const;
  QStringList features() const;
  QVariantList identities() const;
  QVariantList items() const;
  QString queryNode() const;
  QString queryType() const;

  QVariantMap form() const;

  static QVariantMap dataFormToVariantMap(const QXmppDataForm& form);

private:
  const QXmppDiscoveryIq *_discovery;
};

