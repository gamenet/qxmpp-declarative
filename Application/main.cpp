#include <QtGui/QApplication>
#define _CRTDBG_MAP_ALLOC
#include <QtDeclarative/QDeclarativeView>
#include <QtDeclarative/QDeclarativeEngine>


#include <stdlib.h>
#include <crtdbg.h>

int main(int argc, char *argv[])
{
  _CrtDumpMemoryLeaks();
  _CrtSetDbgFlag ( _CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF );

  QApplication app(argc, argv);

  QDeclarativeView view;
  view.setResizeMode(QDeclarativeView::SizeRootObjectToView);
  view.setAttribute(Qt::WA_LockLandscapeOrientation, true);
  
  QString errStr;

#ifdef _DEBUG
  view.engine()->importPlugin(QApplication::applicationDirPath() + QString("/qxmpp-declaratived.dll"), "QXmpp", &errStr);
  view.engine()->importPlugin(QApplication::applicationDirPath() + QString("/qxmpp-declaratived.dll"), "QXmpp", &errStr);
#else
  view.engine()->importPlugin(QApplication::applicationDirPath() + QString("/qxmpp-declarative.dll"), "QXmpp", &errStr);
  view.engine()->importPlugin(QApplication::applicationDirPath() + QString("/qxmpp-declarative.dll"), "QXmpp", &errStr);
#endif

  view.setSource(QApplication::applicationDirPath() + QString("/Main.qml"));
  view.show();

  return app.exec();
}

