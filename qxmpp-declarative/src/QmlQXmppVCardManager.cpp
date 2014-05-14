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

#include <QXmppClient.h>
#include <QXmppConstants.h>

#include <QmlQXmppVCardManager.h>
#include <QmlQXmppVCard.h>

QmlQXmppVCardManager::QmlQXmppVCardManager()
{

}

QmlQXmppVCardManager::~QmlQXmppVCardManager()
{

}

/// This function requests the server for vCard of the specified jid.
/// Once received the signal vCardReceived() is emitted.
///
/// \param jid Jid of the specific entry in the roster
///
QString QmlQXmppVCardManager::requestVCard(const QString& jid)
{
  QXmppVCardIq request(jid);
  if (client()->sendPacket(request)) 
    return request.id();
  
  return QString();
}

/// Returns the vCard of the connected client.
///
/// \return QXmppVCard
///
const QmlQXmppVCard& QmlQXmppVCardManager::clientVCard() const
{
  return this->_clientVCard;
}

/// Sets the vCard of the connected client.
///
/// \param clientVCard QXmppVCard
///
void QmlQXmppVCardManager::setClientVCard(const QmlQXmppVCard& clientVCard)
{
  this->_clientVCard = clientVCard;
  this->_clientVCard.setTo("");
  this->_clientVCard.setFrom("");
  this->_clientVCard.setType(QXmppIq::Set);
  client()->sendPacket(this->_clientVCard);
}

/// This function requests the server for vCard of the connected user itself.
/// Once received the signal clientVCardReceived() is emitted. Received vCard
/// can be get using clientVCard().
QString QmlQXmppVCardManager::requestClientVCard()
{
  return this->requestVCard();
}

/// Returns true if vCard of the connected client has been
/// received else false.
///
/// \return bool
///
bool QmlQXmppVCardManager::isClientVCardReceived() const
{
  return this->_isClientVCardReceived;
}

bool QmlQXmppVCardManager::handleStanza(const QDomElement &element)
{
  if (element.tagName() == "iq" && QXmppVCardIq::isVCard(element)) {
    QmlQXmppVCard vCardIq;
    vCardIq.parse(element);

    if (vCardIq.from().isEmpty()) {
      this->_clientVCard = vCardIq;
      this->_isClientVCardReceived = true;
      emit clientVCardReceived();
    }

    emit this->vCardReceived(&vCardIq);
    
    return true;
  }

  return false;
}
