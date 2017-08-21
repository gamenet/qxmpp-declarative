#include <QmlQXmppPlugin_global.h>

#include <QmlQXmppUserBlacklistManager.h>
#include <QXmppUserBlacklistManager.h>

QmlQXmppUserBlacklistManager::QmlQXmppUserBlacklistManager(QXmppUserBlacklistManager *blackListManager, QObject *parent /*= 0*/)
  : _blackListManager(blackListManager)
  , QObject(parent)
{
  Q_ASSERT(this->_blackListManager);

  SIGNAL_CONNECT_CHECK(connect(this->_blackListManager, SIGNAL(blacklistReceived(QStringList)),
    this, SIGNAL(blacklistReceived(const QStringList&))));

  SIGNAL_CONNECT_CHECK(connect(this->_blackListManager, SIGNAL(blocked(QString)),
    this, SIGNAL(blocked(QString))));

  SIGNAL_CONNECT_CHECK(connect(this->_blackListManager, SIGNAL(unblocked(QString)),
    this, SIGNAL(unblocked(QString))));
}

QmlQXmppUserBlacklistManager::~QmlQXmppUserBlacklistManager()
{
}

void QmlQXmppUserBlacklistManager::requestList()
{
  Q_ASSERT(this->_blackListManager);
  this->_blackListManager->requestList();
}

void QmlQXmppUserBlacklistManager::blockUser(const QString& bareJid)
{
  Q_ASSERT(this->_blackListManager);
  this->_blackListManager->blockUser(bareJid);
}

void QmlQXmppUserBlacklistManager::unblockUser(const QString& bareJid)
{
  Q_ASSERT(this->_blackListManager);
  this->_blackListManager->unblockUser(bareJid);
}
