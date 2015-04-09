#include <QmlQXmppPlugin_global.h>
#include <QmlQXmppBookmarkManager.h>
#include <QXmppBookmarkManager.h>
#include <QXmppBookmarkSet.h>

QmlQXmppBookmarkManager::QmlQXmppBookmarkManager(QXmppBookmarkManager *manager, QObject *parent /*= 0*/)
  : QObject(parent)
  , _manager(manager)
{
  SIGNAL_CONNECT_CHECK(connect(manager, SIGNAL(bookmarksReceived(const QXmppBookmarkSet&)),
    this, SLOT(onBookmarksReceived(const QXmppBookmarkSet&))));
}

QmlQXmppBookmarkManager::~QmlQXmppBookmarkManager()
{
}

void QmlQXmppBookmarkManager::setBookmarks(const QVariantMap &bookmarks)
{
  QXmppBookmarkSet result;

  if (bookmarks.contains("urls")) {
    QList<QXmppBookmarkUrl> bookmarkUrls;

    QVariantList urls = bookmarks["urls"].toList();
    Q_FOREACH(const QVariant &url, urls) {
      QVariantMap urlMap = url.toMap();
      if (!urlMap.contains("url"))
        continue;

      QXmppBookmarkUrl bookmarkUrl;
      bookmarkUrl.setUrl(urlMap["url"].toString());

      if (urlMap.contains("name")) {
        bookmarkUrl.setName(urlMap["name"].toString());
      }

      bookmarkUrls.append(bookmarkUrl);;
    }

    result.setUrls(bookmarkUrls);
  }

  if (bookmarks.contains("conferences")) {
    QList<QXmppBookmarkConference> bookmarkConferences;

    QVariantList conferences = bookmarks["conferences"].toList();
    Q_FOREACH(const QVariant &conference, conferences) {
      QVariantMap conferenceMap = conference.toMap();
      if (!conferenceMap.contains("jid"))
        continue;

      QXmppBookmarkConference bookmarkConference;
      bookmarkConference.setJid(conferenceMap["jid"].toString());

      if (conferenceMap.contains("autojoin"))
        bookmarkConference.setAutoJoin(conferenceMap["autojoin"].toBool());

      if (conferenceMap.contains("name"))
        bookmarkConference.setName(conferenceMap["name"].toString());

      if (conferenceMap.contains("nickName"))
        bookmarkConference.setNickName(conferenceMap["nickName"].toString());

      bookmarkConferences.append(bookmarkConference);;
    }

    result.setConferences(bookmarkConferences);
  }

  this->_manager->setBookmarks(result);
}

void QmlQXmppBookmarkManager::onBookmarksReceived(const QXmppBookmarkSet &bookmarks)
{
  QVariantList urls;
  Q_FOREACH(const QXmppBookmarkUrl& url, bookmarks.urls()) {
    QVariantMap urlMap;
    urlMap["name"] = url.name();
    urlMap["url"] = url.url().toString();
    urls.append(urlMap);
  }

  QVariantList conferences;
  Q_FOREACH(const QXmppBookmarkConference& conference, bookmarks.conferences()) {
    QVariantMap conferenceMap;
    conferenceMap["name"] = conference.name();
    conferenceMap["autoJoin"] = conference.autoJoin();
    conferenceMap["jid"] = conference.jid();
    conferenceMap["nickName"] = conference.nickName();

    conferences.append(conferenceMap);
  }
  
  QVariantMap result;
  result["urls"] = urls;
  result["conferences"] = conferences;
  emit this->received(result);
}
