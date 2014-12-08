#include <QmlQXmppPlugin_global.h>
#include <QmlQXmppLastActivity.h>
#include <QmlQXmppLastActivityManager.h>
#include <QXmppLastActivityIq.h>

#include <QDebug>

QmlQXmppLastActivityManager::QmlQXmppLastActivityManager()
{
  connectSignals();
}

QmlQXmppLastActivityManager::~QmlQXmppLastActivityManager()
{
}

QString QmlQXmppLastActivityManager::requestLastActivity(const QString& bareJid)
{
  return QXmppLastActivityManager::requestLastActivity(bareJid);
}

void QmlQXmppLastActivityManager::onLastActivityReceived(const QXmppLastActivityIq& lastActivity)
{
  QmlQXmppLastActivity translatedActivity(lastActivity.from());
  translatedActivity.setSeconds(lastActivity.seconds());
  translatedActivity.setStatus(lastActivity.status());
  emit this->lastActivityUpdated(&translatedActivity);
}

void QmlQXmppLastActivityManager::connectSignals()
{
  SIGNAL_CONNECT_CHECK(connect(this, SIGNAL(lastActivityReceived(const QXmppLastActivityIq&)), this, SLOT(onLastActivityReceived(const QXmppLastActivityIq&))));
}