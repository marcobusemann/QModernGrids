#pragma once

#include <QModernGrids/Decorators/QmgHeaderdataModelDecorator.h>
#include <QModernGrids/Decorators/QmgSetDataModelDecorator.h>
#include <QModernGrids/Decorators/QmgDataModelDecorator.h>
#include <QModernGrids/Decorators/QmgFetchmoreDecorator.h>

#include <QModernGrids/Builders/QmgHeaderdataModelBuilder.h>
#include <QModernGrids/Builders/QmgDataModelBuilder.h>

#include <QModernGrids/QmgPrivate.h>

#include <QSortFilterProxyModel>
#include <QAbstractItemModel>

class QMODERNGRIDS_LIBRARY_API QmgCommonModelBuilder final
{
public:
   QmgCommonModelBuilder(QAbstractItemModel *base, QObject *parent);
   QmgCommonModelBuilder &operator=(const QmgCommonModelBuilder &other)
   {
      m_base = other.m_base;
      m_parent = other.m_parent;
      return *this;
   }

   template <class T>
   QmgCommonModelBuilder &withObjectData(std::function<QVariant(int, int, const T &)> handler)
   {
      return embeddNewModel(QmgObjectDataModelDecorator::ofType<T>(handler, m_parent));
   }

   template <class T>
   QmgCommonModelBuilder &withProperty(int column, const QString &propertyName)
   {
      return embeddNewModel(QmgObjectPropertyColumnModelDecorator::ofType<T>(column, propertyName, m_parent));
   }

   QmgCommonModelBuilder &withData(QmgDataModelDecorator::Handler handler);
   QmgCommonModelBuilder &withData(QmgDataModelDecorator::RawHandler handler);
   QmgCommonModelBuilder &withData(int role, QmgDataModelDecorator::Handler handler);
   QmgCommonModelBuilder &withData(int role, QmgDataModelDecorator::RawHandler handler);
   QmgDataModelBuilder withData();

   QmgCommonModelBuilder &withSetData(int role, QmgSetDataModelDecorator::Handler handler);

   QmgCommonModelBuilder &withFetchMore(QmgFetchMoreModelDecorator::CanFetchMoreHandler canFetchMoreHandler, QmgFetchMoreModelDecorator::FetchMoreHandler fetchMoreHandler);
   QmgCommonModelBuilder &withHorizontalHeaderData(QmgHeaderDataModelDecorator::Handler handler);
   QmgCommonModelBuilder &withVerticalHeaderData(QmgHeaderDataModelDecorator::Handler handler);
   QmgHeaderDataModelBuilder withHeaderData();

   QmgCommonModelBuilder &withAlternateRowShading(const QColor &colorA, const QColor &colorB);
   QmgCommonModelBuilder &withSortAndFilter(std::function<void(QSortFilterProxyModel*)> handler);
   QmgCommonModelBuilder &withSortAndFilter(QSortFilterProxyModel* sortFilterModel);

   QAbstractProxyModel *build();

   /*
   QmgCommonModelBuilder &withCheckboxMultiMark(
      int column,
      QmgCheckboxMultiMarkModelDecorator::UpdateCheckStateHandler updateHandler,
      QmgCheckboxMultiMarkModelDecorator::IsCheckedHandler checkHandler)
   {
      return embeddNewModel(new QmgCheckboxMultiMarkModelDecorator(column, updateHandler, checkHandler, m_parent));
   }

   template <class T>
   ModelBuilderCommon &withCheckboxMultiMark(int column, std::shared_ptr<ObservableSet<T>> list)
   {
   auto updateHandler = [list](const QVariant &item, bool state) -> void {
   auto typedItem = item.value<T>();
   if (state)
   list->insert(typedItem);
   else
   list->remove(typedItem);
   };

   auto checkHandler = [list](const QVariant &item) -> bool {
   auto typedItem = item.value<T>();
   return list->contains(typedItem);
   };

   return embeddNewModel(new CheckboxMultiMarkModelDecorator(column, updateHandler, checkHandler, m_parent));
   }
   */

private:
   QmgCommonModelBuilder &embeddNewModel(QAbstractProxyModel *model);

   QObject *m_parent;
   QAbstractItemModel *m_base;
};
