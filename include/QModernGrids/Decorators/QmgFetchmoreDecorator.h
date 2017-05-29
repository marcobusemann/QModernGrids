#pragma once

#include <QModernGrids/QmgPrivate.h>

#include <QIdentityProxyModel>

#include <functional>

class QMODERNGRIDS_LIBRARY_API QmgFetchMoreModelDecorator : public QIdentityProxyModel
{
public:
   typedef std::function<bool(const QModelIndex &)> CanFetchMoreHandler;
   typedef std::function<void(const QModelIndex &)> FetchMoreHandler;

public:
   QmgFetchMoreModelDecorator(CanFetchMoreHandler canFetchMoreHandler, FetchMoreHandler fetchMoreHandler, QObject *parent = nullptr);
   virtual void fetchMore(const QModelIndex &parent) override;
   virtual bool canFetchMore(const QModelIndex &parent) const override;

private:
   CanFetchMoreHandler m_canFetchMoreHandler;
   FetchMoreHandler m_fetchMoreHandler;
};