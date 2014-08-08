#include <QmlQXmppPlugin_global.h>
#include <QmlQXmppPEPManager.h>
#include <QmlQXmppGaming.h>

#include <QXmppPEPManager.h>

QmlQXmppPEPManager::QmlQXmppPEPManager(QXmppPEPManager *pepManager, QObject *parent /*= 0*/)
  : _pepManager(pepManager)
  , QObject(parent)
{
  SIGNAL_CONNECT_CHECK(QObject::connect(
    this->_pepManager, SIGNAL(gamingReceived(const QString&, const QString&, const QXmppGaming&)), 
    this, SLOT(onGamingReceived(const QString&, const QString&, const QXmppGaming&))));
}

QmlQXmppPEPManager::~QmlQXmppPEPManager()
{
}

void QmlQXmppPEPManager::setGamingInfo(const QVariantMap& info)
{
  QXmppGaming gaming;

  if (info.contains("characterName"))
    gaming.setCharacterName(info["characterName"].toString());

  if (info.contains("characterProfile"))
    gaming.setCharacterProfile(info["characterProfile"].toString());

  if (info.contains("name"))
    gaming.setName(info["name"].toString());

  if (info.contains("level"))
    gaming.setLevel(info["level"].toString());

  if (info.contains("serverAddress"))
    gaming.setServerAddress(info["serverAddress"].toString());

  if (info.contains("serverName"))
    gaming.setServerName(info["serverName"].toString());

  if (info.contains("uri"))
    gaming.setUri(info["uri"].toString());

  this->_pepManager->sendGaming(gaming);
}

void QmlQXmppPEPManager::onGamingReceived(const QString &jid, const QString &id, const QXmppGaming& game)
{
  QmlQXmppGaming qmlGame(jid, game);
  emit this->gamingReceived(&qmlGame);
}
