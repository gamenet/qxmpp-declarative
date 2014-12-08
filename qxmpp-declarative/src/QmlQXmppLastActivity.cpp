#include <QmlQXmppLastActivity.h>

QmlQXmppLastActivity::QmlQXmppLastActivity(const QString &from)
  : _from(from)
  , _seconds(0)
  , _status(QString())
{

}

QmlQXmppLastActivity::QmlQXmppLastActivity(const QmlQXmppLastActivity &rhs)
  : _seconds(rhs._seconds)
  , _status(rhs._status)
{

}

QmlQXmppLastActivity::~QmlQXmppLastActivity()
{

}

QmlQXmppLastActivity& QmlQXmppLastActivity::operator=(const QmlQXmppLastActivity &rhs)
{
  if (this == &rhs)
    return *this;

  this->_seconds = rhs._seconds;
  this->_status = rhs._status;
  this->_from = rhs._from;
  return *this;
}

void QmlQXmppLastActivity::setFrom(const QString &value)
{
  this->_from = value;
}

QString QmlQXmppLastActivity::from() const
{
  return this->_from;
}

void QmlQXmppLastActivity::setSeconds(quint64 value)
{
  this->_seconds = value;
}

quint64 QmlQXmppLastActivity::seconds() const
{
  return this->_seconds;
}

void QmlQXmppLastActivity::setStatus(const QString &value)
{
  this->_status = value;
}

QString QmlQXmppLastActivity::status() const
{
  return this->_status;
}