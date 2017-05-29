#pragma once

#include <QModernGrids/QmgPrivate.h>

#include <QAbstractProxyModel>

class QMODERNGRIDS_LIBRARY_API QmgProxyModelUtils
{
public:
   static QModelIndex mapFromRoot(QAbstractProxyModel *model, const QModelIndex &rootIndex);
   static QModelIndex mapToRoot(QAbstractProxyModel *model, const QModelIndex &proxyIndex);
};