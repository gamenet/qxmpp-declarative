/*
 * The MIT License (MIT)
 * 
 * Copyright (c) 2014 GameNet
 * 
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *  
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 * 
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 */

#pragma once

#include <QtCore/QObject>
#include <QXmppMessage.h>

class QmlQXmppMessage : public QObject
{
    Q_OBJECT

    Q_ENUMS(Type)
    Q_ENUMS(State)
    Q_PROPERTY(QString body READ body)
    Q_PROPERTY(bool isAttentionRequested READ isAttentionRequested);
    Q_PROPERTY(bool isReplaceMessage READ isReplaceMessage);
    Q_PROPERTY(bool isReceiptRequested READ isReceiptRequested);
    Q_PROPERTY(QString mucInvitationJid READ mucInvitationJid);
    Q_PROPERTY(QString mucInvitationPassword READ mucInvitationPassword);
    Q_PROPERTY(QString mucInvitationReason READ mucInvitationReason);
    Q_PROPERTY(QString receiptId READ receiptId);
    Q_PROPERTY(QDateTime stamp READ stamp);
    Q_PROPERTY(QString subject READ subject);
    Q_PROPERTY(QString thread READ thread);
    Q_PROPERTY(QString xhtml READ xhtml);
    Q_PROPERTY(QmlQXmppMessage::State state READ state);
    Q_PROPERTY(QmlQXmppMessage::Type type READ type);

    Q_PROPERTY(QString to READ to);
    Q_PROPERTY(QString from READ from);
    Q_PROPERTY(QString id READ id);
    Q_PROPERTY(QString lang READ lang);

public:
    enum Type
    {
        Error = QXmppMessage::Error,
        Normal = QXmppMessage::Normal,
        Chat = QXmppMessage::Chat,
        GroupChat = QXmppMessage::GroupChat,
        Headline = QXmppMessage::Headline
    };

    enum State
    {
        None = QXmppMessage::None, 
        Active = QXmppMessage::Active,
        Inactive = QXmppMessage::Inactive,
        Gone = QXmppMessage::Gone,
        Composing = QXmppMessage::Composing,
        Paused = QXmppMessage::Paused,
    };

    QmlQXmppMessage(QObject *parent = 0);
    QmlQXmppMessage(const QXmppMessage &other, QObject *parent = 0);
    ~QmlQXmppMessage();

    QmlQXmppMessage& operator=(const QXmppMessage &other);

    QString body() const;
    bool isAttentionRequested() const;
    bool isReceiptRequested() const;
    bool isReplaceMessage() const;
    QString mucInvitationJid() const;
    QString mucInvitationPassword() const;
    QString mucInvitationReason() const;
    QString receiptId() const;
    QDateTime stamp() const;
    State state() const;
    QString subject() const;
    QString thread() const;
    Type type() const;
    QString xhtml() const;
    QString to() const;
    QString from() const;
    QString id() const;
    QString lang() const;
    QXmppStanza::Error error() const;

    static QXmppMessage::Type parseMessageType(int type);
    static QXmppMessage::State parseMessageState(int state);

private:
    QXmppMessage _message;
};
