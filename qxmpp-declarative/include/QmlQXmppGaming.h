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
#include <QXmppGaming.h>

class QmlQXmppGaming : public QObject
{
  Q_OBJECT
  Q_PROPERTY(QString from READ from);
  Q_PROPERTY(QString characterName READ characterName);
  Q_PROPERTY(QString characterProfile READ characterProfile);
  Q_PROPERTY(QString name READ name);
  Q_PROPERTY(QString level READ level);
  Q_PROPERTY(QString serverAddress READ serverAddress);
  Q_PROPERTY(QString serverName READ serverName);
  Q_PROPERTY(QString uri READ uri);
public:
  QmlQXmppGaming(QObject *parent = 0);
  QmlQXmppGaming(const QString& from, const QXmppGaming& gaming, QObject *parent = 0);
  virtual ~QmlQXmppGaming();

  QString from() const;
  QString characterName() const;
  QString characterProfile() const;
  QString name() const;
  QString level() const;
  QString serverAddress() const;
  QString serverName() const;
  QString uri() const;

private:
  QXmppGaming _gaming;
  QString _from;
};

