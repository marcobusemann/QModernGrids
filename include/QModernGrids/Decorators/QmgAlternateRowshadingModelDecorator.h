#pragma once

#include <QModernGrids/QmgPrivate.h>

#include <QIdentityProxyModel>
#include <QColor>

class QMODERNGRIDS_LIBRARY_API QmgAlternateRowShadingModelDecorator : public QIdentityProxyModel
{
public:
   QmgAlternateRowShadingModelDecorator(const QColor &colorA, const QColor &colorB, QObject *parent = nullptr);
   virtual QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;

private:
   QColor m_colorA;
   QColor m_colorB;
};
