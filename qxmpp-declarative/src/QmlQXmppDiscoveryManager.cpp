#include <QmlQXmppPlugin_global.h>
#include <QmlQXmppDiscoveryManager.h>
#include <QmlQXmppDiscovery.h>

#include <QXmppDiscoveryManager.h>
#include <QXmppDiscoveryIq.h>

QmlQXmppDiscoveryManager::QmlQXmppDiscoveryManager(QXmppDiscoveryManager *manager, QObject *parent /*= 0*/)
  : QObject(parent)
  , _manager(manager)
{
  SIGNAL_CONNECT_CHECK(connect(manager, SIGNAL(infoReceived(const QXmppDiscoveryIq&)),
    this, SLOT(onInfoReceived(const QXmppDiscoveryIq&))));
  SIGNAL_CONNECT_CHECK(connect(manager, SIGNAL(itemsReceived(const QXmppDiscoveryIq&)),
    this, SLOT(onItemsReceived(const QXmppDiscoveryIq&))));
}

QmlQXmppDiscoveryManager::~QmlQXmppDiscoveryManager()
{
}

QString QmlQXmppDiscoveryManager::requestInfo(const QString& jid, const QString& node /*= QString()*/)
{
  return this->_manager->requestInfo(jid, node);
}

QString QmlQXmppDiscoveryManager::requestItems(const QString& jid, const QString& node /*= QString()*/)
{
  return this->_manager->requestItems(jid, node);
}

void QmlQXmppDiscoveryManager::onInfoReceived(const QXmppDiscoveryIq& info)
{
  QmlQXmppDiscovery qmlInfo(&info, this);
  emit this->infoReceived(&qmlInfo);
}

void QmlQXmppDiscoveryManager::onItemsReceived(const QXmppDiscoveryIq& items)
{
  QmlQXmppDiscovery qmlInfo(&items, this);
  emit this->itemsReceived(&qmlInfo);
}
