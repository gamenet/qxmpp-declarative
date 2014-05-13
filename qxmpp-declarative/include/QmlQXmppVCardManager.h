#pragma once

#include <QXmppVCardManager.h>

#include <QmlQXmppVCard.h>

class QmlQXmppVCardManager : public QXmppVCardManager
{
  Q_OBJECT

public:
  QmlQXmppVCardManager();
  ~QmlQXmppVCardManager();

  void setExtraFields(const QStringList &extraElements = QStringList() << "EXTRA");
  QStringList extraFields() const;

  Q_INVOKABLE QString requestVCard(const QString& bareJid = "");

  Q_INVOKABLE const QmlQXmppVCard& clientVCard() const;
  Q_INVOKABLE void setClientVCard(const QmlQXmppVCard&);

  Q_INVOKABLE QString requestClientVCard();
  Q_INVOKABLE bool isClientVCardReceived() const;

  bool handleStanza(const QDomElement &element);

signals:
  /// This signal is emitted when the requested vCard is received
  /// after calling the requestVCard() function.
  void vCardReceived(QmlQXmppVCard *vcard);
  //void vCardReceived(const QString& vcard);

  /// This signal is emitted when the client's vCard is received
  /// after calling the requestClientVCard() function.
  void clientVCardReceived();

private:
  QmlQXmppVCard _clientVCard;
  bool _isClientVCardReceived;
  QStringList _customElements;
};