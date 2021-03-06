#pragma once

#include <QModernGrids/QmgObservableVariantListProxy.h>
#include <QModernGrids/QmgPrivate.h>

#include <QAbstractItemModel>

#include <functional>
#include <memory>

class QMODERNGRIDS_LIBRARY_API QmgObservableVariantListModel : public QAbstractItemModel
{
public:
   QmgObservableVariantListModel(QObject *parent = nullptr);
   void setSource(const QmgObservableVariantListProxy &source);
   virtual QModelIndex index(int row, int column, const QModelIndex &parent = QModelIndex()) const override;
   virtual QModelIndex parent(const QModelIndex &) const override;
   virtual int rowCount(const QModelIndex &parent = QModelIndex()) const override;
   virtual int columnCount(const QModelIndex & = QModelIndex()) const override;
   virtual QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;
   virtual QModelIndexList match(const QModelIndex &start, int role, const QVariant &value, int hits = 1, Qt::MatchFlags flags = Qt::MatchFlags(Qt::MatchStartsWith | Qt::MatchWrap)) const;

   virtual bool insertRows(int row, int count, const QModelIndex &parent = QModelIndex()) override;
   virtual bool setData(const QModelIndex &index, const QVariant &value, int role = Qt::EditRole) override;
   virtual bool removeRows(int row, int count, const QModelIndex &parent = QModelIndex());

private:
   void linkTo(QmgObservableVariantListProxy &source);
   void unlinkFrom(QmgObservableVariantListProxy &source);

   QmgObservableVariantListProxy m_source;

   QmgScopePtr m_addBeforeScope;
   QmgScopePtr m_addAfterScope;
   QmgScopePtr m_addBatchBeforeScope;
   QmgScopePtr m_addBatchAfterScope;
   QmgScopePtr m_removeBeforeScope;
   QmgScopePtr m_removeAfterScope;
   QmgScopePtr m_updateAfterScope;
   QmgScopePtr m_clearBeforeScope;
   QmgScopePtr m_clearAfterScope;
};
