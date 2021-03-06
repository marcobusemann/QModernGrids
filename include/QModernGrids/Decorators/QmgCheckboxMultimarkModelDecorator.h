#pragma once

#include <QModernGrids/QmgPrivate.h>

#include <QIdentityProxyModel>
#include <functional>

class QMODERNGRIDS_LIBRARY_API QmgCheckboxMultiMarkModelDecorator : public QIdentityProxyModel
{
public:
   typedef std::function<void(const QVariant &item, bool)> UpdateCheckStateHandler;
   typedef std::function<bool(const QVariant &item)> IsCheckedHandler;

public:
   QmgCheckboxMultiMarkModelDecorator(
      int column,
      UpdateCheckStateHandler updateHandler,
      IsCheckedHandler checkHandler,
      QObject *parent = nullptr);

   QmgCheckboxMultiMarkModelDecorator(
      UpdateCheckStateHandler updateHandler,
      IsCheckedHandler checkHandler,
      QObject *parent = nullptr);

   virtual QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;
   virtual bool setData(const QModelIndex &index, const QVariant &value, int role = Qt::EditRole) override;
   virtual Qt::ItemFlags flags(const QModelIndex &index) const override;

private:
   int m_column;
   UpdateCheckStateHandler m_updateHandler;
   IsCheckedHandler m_checkHandler;
};
