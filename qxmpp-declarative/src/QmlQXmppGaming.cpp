#include <QmlQXmppGaming.h>

QmlQXmppGaming::QmlQXmppGaming(const QString& from, const QXmppGaming& gaming, QObject *parent /*= 0*/)
  : _from(from)
  , _gaming(gaming)
  , QObject(parent)
{
}

QmlQXmppGaming::QmlQXmppGaming(QObject *parent /*= 0*/)
  : QObject(parent)
{
}

QmlQXmppGaming::~QmlQXmppGaming()
{
}

QString QmlQXmppGaming::characterName() const
{
  return this->_gaming.characterName();
}

QString QmlQXmppGaming::characterProfile() const
{
  return this->_gaming.characterProfile();
}

QString QmlQXmppGaming::name() const
{
  return this->_gaming.name();
}

QString QmlQXmppGaming::level() const
{
  return this->_gaming.level();
}

QString QmlQXmppGaming::serverAddress() const
{
  return this->_gaming.serverAddress();
}

QString QmlQXmppGaming::serverName() const
{
  return this->_gaming.serverName();
}

QString QmlQXmppGaming::uri() const
{
  return this->_gaming.uri();
}

QString QmlQXmppGaming::from() const
{
  return this->_from;
}
