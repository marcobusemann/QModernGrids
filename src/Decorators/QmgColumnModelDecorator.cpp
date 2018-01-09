#include <QModernGrids/Decorators/QmgColumnModelDecorator.h>
#include <QModernGrids/QmgModelLogger.h>

QmgColumnModelDecorator::QmgColumnModelDecorator(int columns, QObject *parent)
   : QIdentityProxyModel(parent)
   , m_columns(columns)
{
}

void QmgColumnModelDecorator::setSourceModel(QAbstractItemModel *sourceModel)
{
   if (this->sourceModel())
      disconnect(this->sourceModel());

   QIdentityProxyModel::setSourceModel(sourceModel);

   if (this->sourceModel())
      connect(this->sourceModel(), SIGNAL(dataChanged(QModelIndex, QModelIndex)), this, SLOT(forwardDataChanged(QModelIndex, QModelIndex)));
}

int QmgColumnModelDecorator::columnCount(const QModelIndex &index) const
{
   QmgModelLogger::instance().logColumnCount("ColumnModelDecorator::columnCount", index, m_columns);
   return m_columns;
}

bool QmgColumnModelDecorator::hasChildren(const QModelIndex &parent) const
{
   return (rowCount(parent) > 0) && (columnCount(parent) > 0);
}

void QmgColumnModelDecorator::forwardDataChanged(const QModelIndex &topLeft, const QModelIndex &bottomRight)
{
   const auto realBottomRight = bottomRight.sibling(bottomRight.row(), columnCount() - 1);
   emit dataChanged(mapFromSource(topLeft), mapFromSource(realBottomRight));
}
