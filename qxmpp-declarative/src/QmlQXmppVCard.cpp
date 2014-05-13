#include <QmlQXmppVCard.h>

QmlQXmppVCard::QmlQXmppVCard(const QStringList &customElements)
  : _customElements(customElements)
{

}

QmlQXmppVCard::QmlQXmppVCard(const QmlQXmppVCard &p)
{

}

QmlQXmppVCard::~QmlQXmppVCard()
{

}

QmlQXmppVCard& QmlQXmppVCard::operator=(const QmlQXmppVCard &xmppVCard)
{
  this->_customElements = xmppVCard._customElements;
  return *this;
}

void QmlQXmppVCard::setExtra(const QVariantMap &map)
{
  this->_extraData = map;
}

QVariantMap QmlQXmppVCard::extra() const
{
  return this->_extraData;
}

void QmlQXmppVCard::setCustomElements(const QStringList &customElements)
{
  this->_customElements = customElements;
}

QStringList QmlQXmppVCard::customElements() const
{
  return this->_customElements;
}

void QmlQXmppVCard::parseElementFromChild(const QDomElement &nodeRecv)
{
  QXmppVCardIq::parseElementFromChild(nodeRecv);
  QDomElement cardElement = nodeRecv.firstChildElement("vCard");
  QDomElement child = cardElement.firstChildElement();
  while (!child.isNull()) {
    QString elementName = child.tagName();
    if (elementName == "EXTRA") {
      QDomElement extraChild = child.firstChildElement();
      while (!extraChild.isNull()) {
        QString keyName = extraChild.tagName();
        QString value = extraChild.text();
        this->_extraData.insert(keyName, value);

        extraChild = extraChild.nextSiblingElement();
      }
    }
    child = child.nextSiblingElement();
  }
}

void QmlQXmppVCard::toXmlElementFromChild(QXmlStreamWriter *writer) const
{
  QXmppVCardIq::toXmlElementFromChild(writer);

  writer->writeStartElement("EXTRA");

  QVariantMap::const_iterator it = this->_extraData.constBegin();
  for (; it != this->_extraData.constEnd(); ++it) {
    writer->writeTextElement(it.key(), it.value().toString());
  }

  writer->writeEndElement();
}
