#pragma once

#include <QModernGrids/Builders/QmgCommonModelBuilder.h>
#include <QModernGrids/Builders/QmgColumnModelBuilder.h>
#include <QModernGrids/QmgObservableVariantListProxy.h>
#include <QModernGrids/QmgPrivate.h>

class QAbstractItemModel;

class QMODERNGRIDS_LIBRARY_API QmgSourceModelBuilder final
{
public:
   QmgSourceModelBuilder(const QmgObservableVariantListProxy &list, QObject *parent);
   QmgCommonModelBuilder withColumns(int columns);
   QmgCommonModelBuilder withColumns(const QList<QmgColumnModelBuilder> columnModelBuilders);

private:
   QObject * const m_parent;
   QAbstractItemModel *m_base;
};
