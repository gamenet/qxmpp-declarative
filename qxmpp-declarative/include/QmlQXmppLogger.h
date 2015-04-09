#pragma once

#include <QtCore/QObject>

#include <QXmppLogger.h>

class QXmppClient;

class QmlQXmppLogger : public QObject
{
  Q_OBJECT
  Q_ENUMS(MessageTypes)
  Q_PROPERTY(bool enabled READ enabled WRITE setEnabled NOTIFY enabledChanged);
public:
  /// This enum describes a type of log message.
  enum MessageType
  {
    NoMessage = QXmppLogger::NoMessage,                    ///< No message type
    DebugMessage = QXmppLogger::DebugMessage,              ///< Debugging message
    InformationMessage = QXmppLogger::InformationMessage,  ///< Informational message
    WarningMessage = QXmppLogger::WarningMessage,          ///< Warning message
    ReceivedMessage = QXmppLogger::ReceivedMessage,        ///< Message received from server
    SentMessage = QXmppLogger::SentMessage,                ///< Message sent to server
    AnyMessage = QXmppLogger::AnyMessage,                  ///< Any message type
  };
  Q_DECLARE_FLAGS(MessageTypes, MessageType)

  QmlQXmppLogger(QXmppClient *client, QObject *parent = 0);
  virtual ~QmlQXmppLogger();

  void setEnabled(bool value);
  bool enabled() const;

signals:
  void enabledChanged();

  void message(int type, const QString& message);

private slots:
  void onLogMessage(QXmppLogger::MessageType type, const QString & message);

private:
  QXmppClient *_client;
  bool _enabled;
};

