#include <QmlQXmppPlugin_global.h>

#include <QmlQXmppLogger.h>

#include <QXmppClient.h>

QmlQXmppLogger::QmlQXmppLogger(QXmppClient *client, QObject *parent /*= 0*/)
  : QObject(parent)
  , _client(client)
  , _enabled(false)
{
  SIGNAL_CONNECT_CHECK(connect(this->_client->logger(), SIGNAL(message(QXmppLogger::MessageType , const QString &)),
    this, SLOT(onLogMessage(QXmppLogger::MessageType , const QString &))));
}

QmlQXmppLogger::~QmlQXmppLogger()
{
}

void QmlQXmppLogger::setEnabled(bool value)
{
  if (this->_enabled == value)
    return;

  this->_client->logger()->setLoggingType(
    value ? QXmppLogger::SignalLogging : QXmppLogger::NoLogging);
  this->_enabled = value;
}

bool QmlQXmppLogger::enabled() const
{
  return this->_enabled;
}

void QmlQXmppLogger::onLogMessage(QXmppLogger::MessageType type, const QString & message)
{
  emit this->message(static_cast<QmlQXmppLogger::MessageType>(type), message);
}
