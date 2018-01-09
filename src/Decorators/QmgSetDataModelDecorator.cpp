
#include <QModernGrids/Decorators/QmgSetDataModelDecorator.h>
#include <QSet>

QmgSetDataModelDecorator::QmgSetDataModelDecorator(Handler handler, QObject *parent)
   : QIdentityProxyModel(parent)
   , m_handler(handler)
   , m_excludeRoles(QSet<int>() << Qt::UserRole)
{}

QmgSetDataModelDecorator::QmgSetDataModelDecorator(const QSet<int> &roleExcludes, Handler handler, QObject *parent)
   : QIdentityProxyModel(parent)
   , m_handler(handler)
   , m_excludeRoles(roleExcludes)
{}

bool QmgSetDataModelDecorator::setData(const QModelIndex &index, const QVariant &value, int role)
{
   if (m_excludeRoles.contains(role))
      return QIdentityProxyModel::setData(index, value, role);
   if (!index.isValid())
      return false;
   return m_handler(mapToSource(index), value);
}

QmgColumnBasedSetDataModelDecorator::QmgColumnBasedSetDataModelDecorator(int column, Handler handler, QObject *parent)
   : QmgSetDataModelDecorator(handler, parent)
   , m_column(column)
{}

QmgColumnBasedSetDataModelDecorator::QmgColumnBasedSetDataModelDecorator(int column, const QSet<int> &roleExcludes, Handler handler, QObject *parent)
   : QmgSetDataModelDecorator(roleExcludes, handler, parent)
   , m_column(column)
{}

bool QmgColumnBasedSetDataModelDecorator::setData(const QModelIndex &index, const QVariant &value, int role)
{
   return index.column() == m_column ?
      QmgSetDataModelDecorator::setData(index, value, role) :
      QIdentityProxyModel::setData(index, value, role);
}

QmgRoleBasedSetDataModelDecorator::QmgRoleBasedSetDataModelDecorator(int role, Handler handler, QObject *parent)
   : QmgSetDataModelDecorator(handler, parent)
   , m_role(role)
{}

bool QmgRoleBasedSetDataModelDecorator::setData(const QModelIndex &index, const QVariant &value, int role)
{
   return role == m_role ?
      QmgSetDataModelDecorator::setData(index, value, role) :
      QIdentityProxyModel::setData(index, value, role);
}

QmgColumnAndRoleBasedSetDataModelDecorator::QmgColumnAndRoleBasedSetDataModelDecorator(int column, int role, Handler handler, QObject *parent)
   : QmgSetDataModelDecorator(handler, parent)
   , m_column(column)
   , m_role(role)
{}

bool QmgColumnAndRoleBasedSetDataModelDecorator::setData(const QModelIndex &index, const QVariant &value, int role)
{
   return index.column() == m_column && role == m_role ?
      QmgSetDataModelDecorator::setData(index, value, role) :
      QIdentityProxyModel::setData(index, value, role);
}