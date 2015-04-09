#include <QmlQXmppDiscovery.h>
#include <QXmppDiscoveryIq.h>

QString dataFormTypeToString(QXmppDataForm::Type type)
{
  switch(type) {
  case QXmppDataForm::Form:
    return "form";
  case QXmppDataForm::Submit:
    return "submit";
  case QXmppDataForm::Cancel:
    return "cancel";
  case QXmppDataForm::Result:
    return "result";
  case QXmppDataForm::None:
    return "none";
  default:
    return "none";
  }
}

QXmppDataForm::Type dataFormTypeFromString(const QString& type)
{
  if (type == "form")
    return QXmppDataForm::Form;

  if (type == "submit")
    return QXmppDataForm::Submit;

  if (type == "cancel")
    return QXmppDataForm::Cancel;

  if (type == "result")
    return QXmppDataForm::Result;

  return QXmppDataForm::None;
}

QString fieldTypeToString(QXmppDataForm::Field::Type type)
{
  switch(type) {
  case QXmppDataForm::Field::BooleanField:
    return "boolean";
  case QXmppDataForm::Field::FixedField:
    return "fixed";
  case QXmppDataForm::Field::HiddenField:
    return "hidden";
  case QXmppDataForm::Field::JidMultiField:
    return "jid-multi";
  case QXmppDataForm::Field::JidSingleField:
    return "jid-single";
  case QXmppDataForm::Field::ListMultiField:
    return "list-multi";
  case QXmppDataForm::Field::ListSingleField:
    return "list-single";
  case QXmppDataForm::Field::TextMultiField:
    return "text-multi";
  case QXmppDataForm::Field::TextPrivateField:
    return "text-private";
  case QXmppDataForm::Field::TextSingleField:
    return "text-single";

  default:
    return "";
  }
}


QmlQXmppDiscovery::QmlQXmppDiscovery(const QXmppDiscoveryIq *discovery, QObject* parent /*= 0*/)
  : QObject(parent)
  , _discovery(discovery)
{
}

QmlQXmppDiscovery::QmlQXmppDiscovery(const QmlQXmppDiscovery &p)
  : QObject()
  , _discovery(p._discovery)
{
}

QmlQXmppDiscovery::QmlQXmppDiscovery()
  : QObject()
  , _discovery(0)
{
}

QmlQXmppDiscovery::~QmlQXmppDiscovery()
{
}

QmlQXmppDiscovery& QmlQXmppDiscovery::operator=(const QmlQXmppDiscovery &rhs)
{
  if (this == &rhs)
    return *this;

  this->_discovery = rhs._discovery;
  return *this;
}

QString QmlQXmppDiscovery::id() const
{
  return this->_discovery->id();
}

QStringList QmlQXmppDiscovery::features() const
{
  return this->_discovery->features();
}

QVariantList QmlQXmppDiscovery::identities() const
{
  QVariantList result;
  Q_FOREACH(const QXmppDiscoveryIq::Identity& identity, this->_discovery->identities()) {
    QVariantMap identityMap;
    identityMap["category"] = identity.category();
    identityMap["language"] = identity.language();
    identityMap["name"] = identity.name();
    identityMap["type"] = identity.type();
    result.append(identityMap);
  }

  return result;
}

QVariantList QmlQXmppDiscovery::items() const
{
  QVariantList result;
  Q_FOREACH(const QXmppDiscoveryIq::Item& item, this->_discovery->items()) {
    QVariantMap itemMap;
    itemMap["jid"] = item.jid();
    itemMap["name"] = item.name();
    itemMap["node"] = item.node();
    result.append(itemMap);
  }

  return result;
}

QString QmlQXmppDiscovery::queryNode() const
{
  return this->_discovery->queryNode();
}

QString QmlQXmppDiscovery::queryType() const
{
  switch (this->_discovery->queryType())
  {
  case QXmppDiscoveryIq::InfoQuery:
    return QString("info");
  case QXmppDiscoveryIq::ItemsQuery:
    return QString("items");
  default:
    return QString();
  }
}

QVariantMap QmlQXmppDiscovery::form() const
{
  return dataFormToVariantMap(this->_discovery->form());
}

QVariantMap QmlQXmppDiscovery::dataFormToVariantMap(const QXmppDataForm& form)
{
  QVariantMap result;

  result["instructions"] = form.instructions();
  result["title"] = form.title();
  result["type"] = dataFormTypeToString(form.type());

  QVariantList fields;
  Q_FOREACH(const QXmppDataForm::Field &field, form.fields()) {
    QVariantMap fieldMap;
    fieldMap["description"] = field.description();
    fieldMap["key"] = field.key();
    fieldMap["label"] = field.label();
    fieldMap["description"] = field.description();
    fieldMap["value"] = field.value();
    fieldMap["type"] = fieldTypeToString(field.type());

    fields.append(fieldMap);
  }

  result["fields"] = fields;
  return result;
}
