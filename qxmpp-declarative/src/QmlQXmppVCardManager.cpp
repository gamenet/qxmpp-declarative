#include <QtCore/QDebug>

#include <QmlQXmppVCardManager.h>

#define SIGNAL_CONNECT_CHECK(X) { bool result = X; Q_ASSERT_X(result, __FUNCTION__ , #X); }

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
   qDebug() << "QmlQXmppVCardManager::requestVCard - " << jid;

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
