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

#include <QmlQXmppPlugin_global.h>
#include <QmlQXmppVCardManager.h>

QmlQXmppVCardManager::QmlQXmppVCardManager(QXmppVCardManager *vcardMgr, QObject *parent)
  : QObject(parent)
  , _vcardManager(vcardMgr)
{
  this->connectSignals();
}

QmlQXmppVCardManager::~QmlQXmppVCardManager()
{

}

void QmlQXmppVCardManager::requestVCard(const QString& jid)
{
   Q_ASSERT(_vcardManager);
 
   _vcardManager->requestVCard(jid);
 }

void QmlQXmppVCardManager::onVCardReceived(const QXmppVCardIq& vcardIq)
{
  QmlQXmppVCard vcardWrapper;
  vcardWrapper = vcardIq;
  //QSharedPointer<QmlQXmppVCard> ptr(vcardWrapper);
  //_requestedVCards.append(ptr);
  emit vCardReceived(&vcardWrapper);
}

void QmlQXmppVCardManager::connectSignals()
{
  Q_ASSERT(_vcardManager);

  SIGNAL_CONNECT_CHECK(connect(_vcardManager, SIGNAL(vCardReceived(const QXmppVCardIq&)), this, SLOT(onVCardReceived(const QXmppVCardIq&))));
}
