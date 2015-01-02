TEMPLATE = lib
TARGET = qxmpp-declarative
QT += qml quick network xml
CONFIG += qt plugin
CONFIG += c++11

## include qxmpp library
CONFIG += link_pkgconfig
PKGCONFIG += qxmpp

TARGET = $$qtLibraryTarget($$TARGET)
uri = QXmpp

# Input
SOURCES += \
    src/QmlQXmppArchiveManager.cpp \
    src/QmlQXmppClient.cpp \
    src/QmlQXmppConfiguration.cpp \
    src/QmlQXmppMessage.cpp \
    src/QmlQXmppPlugin.cpp \
    src/QmlQXmppPresence.cpp \
    src/QmlQXmppRosterManager.cpp \
    src/QmlQXmppVCard.cpp \
    src/QmlQXmppVCardManager.cpp

HEADERS += \
    include/QmlQXmppArchiveManager.h \
    include/QmlQXmppClient.h \
    include/QmlQXmppConfiguration.h \
    include/QmlQXmppMessage.h \
    include/QmlQXmppPlugin_global.h \
    include/QmlQXmppPlugin.h \
    include/QmlQXmppPresence.h \
    include/QmlQXmppRosterManager.h \
    include/QmlQXmppVCard.h \
    include/QmlQXmppVCardManager.h

INCLUDEPATH = include/

DISTFILES = qmldir

!equals(_PRO_FILE_PWD_, $$OUT_PWD) {
    copy_qmldir.target = $$OUT_PWD/qmldir
    copy_qmldir.depends = $$_PRO_FILE_PWD_/qmldir
    copy_qmldir.commands = $(COPY_FILE) \"$$replace(copy_qmldir.depends, /, $$QMAKE_DIR_SEP)\" \"$$replace(copy_qmldir.target, /, $$QMAKE_DIR_SEP)\"
    QMAKE_EXTRA_TARGETS += copy_qmldir
    PRE_TARGETDEPS += $$copy_qmldir.target
}

qmldir.files = qmldir
unix {
    installPath = $$[QT_INSTALL_QML]/$$replace(uri, \\., /)
    qmldir.path = $$installPath
    target.path = $$installPath
    INSTALLS += target qmldir
}

