#pragma once

#include <QModernGrids/Decorators/QmgHeaderdataModelDecorator.h>
#include <QModernGrids/QmgPrivate.h>

#include <QAbstractItemModel>

class QmgCommonModelBuilder;

class QMODERNGRIDS_LIBRARY_API QmgHeaderDataModelBuilder final
{
public:
   QmgHeaderDataModelBuilder(QAbstractItemModel *base, QObject *parent);
   QmgHeaderDataModelBuilder &forSection(int section);
   QmgHeaderDataModelBuilder &forRole(int role);
   QmgHeaderDataModelBuilder &withOrientation(Qt::Orientation orientation);
   QmgCommonModelBuilder withHandler(QmgHeaderDataModelDecorator::Handler handler);

private:
   QObject * const m_parent;
   int m_section;
   int m_role;
   Qt::Orientation m_orientation;
   QAbstractItemModel *m_base;
};
