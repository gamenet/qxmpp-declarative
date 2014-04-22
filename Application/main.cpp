#include <QtWidgets/QApplication>
#include <QtDeclarative/QDeclarativeView>
#include <QtDeclarative/QDeclarativeEngine>

int main(int argc, char *argv[])
{
  QApplication app(argc, argv);

  QDeclarativeView view;
  view.setResizeMode(QDeclarativeView::SizeRootObjectToView);
  
  QString errStr;

#ifdef _DEBUG
  view.engine()->importPlugin(QApplication::applicationDirPath() + QString("/qxmpp-declaratived.dll"), "QXmpp", &errStr);
  view.engine()->importPlugin(QApplication::applicationDirPath() + QString("/qxmpp-declaratived.dll"), "QXmpp", &errStr);
#else
  view.engine()->importPlugin(QApplication::applicationDirPath() + QString("/qxmpp-declarative.dll"), "QXmpp", &errStr);
  view.engine()->importPlugin(QApplication::applicationDirPath() + QString("/qxmpp-declarative.dll"), "QXmpp", &errStr);
#endif

  view.setSource(QUrl::fromLocalFile(QApplication::applicationDirPath() + QString("/Main.qml")));
  view.show();

  return app.exec();
}