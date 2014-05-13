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

void QmlQXmppVCardManager::setExtraFields(const QStringList &extraElements)
{
  this->_customElements = extraElements;
}

QStringList QmlQXmppVCardManager::extraFields() const
{
  return this->_customElements;
}

/// This function requests the server for vCard of the specified jid.
/// Once received the signal vCardReceived() is emitted.
///
/// \param jid Jid of the specific entry in the roster
///
QString QmlQXmppVCardManager::requestVCard(const QString& jid)
{
  QXmppVCardIq request(jid);
  if (client()->sendPacket(request)) {
    return request.id();
  } else {
    return QString();
  }
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
  return requestVCard();
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
  if(element.tagName() == "iq" && QXmppVCardIq::isVCard(element))
  {
    QmlQXmppVCard vCardIq(this->_customElements);
    vCardIq.parse(element);

    if (vCardIq.from().isEmpty()) {
      this->_clientVCard = vCardIq;
      this->_isClientVCardReceived = true;
      emit clientVCardReceived();
    }
    emit vCardReceived(&vCardIq);
    
    return true;
  }

  return false;
}
