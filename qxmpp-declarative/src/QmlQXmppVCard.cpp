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

#include <QmlQXmppVCard.h>

QmlQXmppVCard::QmlQXmppVCard(const QString &elementName)
  : _extraElementName(elementName)
{

}

QmlQXmppVCard::QmlQXmppVCard(const QmlQXmppVCard &rhs)
  : _extraElementName(rhs._extraElementName)
  , _extraData(rhs._extraData)
{

}

QmlQXmppVCard::~QmlQXmppVCard()
{

}

QmlQXmppVCard& QmlQXmppVCard::operator=(const QmlQXmppVCard &rhs)
{
  if (this == &rhs)
    return *this;

  this->_extraElementName = rhs._extraElementName;
  this->_extraData = rhs._extraData;
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

void QmlQXmppVCard::setExtraElementName(const QString &elementName)
{
  this->_extraElementName = elementName;
}

QString QmlQXmppVCard::extraElementName() const
{
  return this->_extraElementName;
}

void QmlQXmppVCard::parseElementFromChild(const QDomElement &nodeRecv)
{
  QXmppVCardIq::parseElementFromChild(nodeRecv);
  QDomElement child = nodeRecv.firstChildElement("vCard")
                              .firstChildElement();

  while (!child.isNull()) {
    QString elementName = child.tagName();
    if (elementName == this->_extraElementName) {
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

  if (!this->_extraElementName.isEmpty()) {
    writer->writeStartElement(this->_extraElementName);

    QVariantMap::const_iterator it = this->_extraData.constBegin();
    for (; it != this->_extraData.constEnd(); ++it) {
      writer->writeTextElement(it.key(), it.value().toString());
    }

    writer->writeEndElement();
  }
}
