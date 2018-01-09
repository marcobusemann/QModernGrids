#pragma once

#include <QModernGrids/QmgPrivate.h>

#include <QIdentityProxyModel>

class QMODERNGRIDS_LIBRARY_API QmgColumnModelDecorator : public QIdentityProxyModel
{
   Q_OBJECT

public:
   QmgColumnModelDecorator(int columns, QObject *parent = nullptr);
   virtual void setSourceModel(QAbstractItemModel *sourceModel) override;
   virtual int	columnCount(const QModelIndex & = QModelIndex()) const override;
   virtual bool hasChildren(const QModelIndex &parent) const override;

private:
   int m_columns;

private slots:
   void forwardDataChanged(const QModelIndex &topLeft, const QModelIndex &bottomRight);
};
