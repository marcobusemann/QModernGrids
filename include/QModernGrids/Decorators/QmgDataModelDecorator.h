#pragma once

#include <QModernGrids/QmgPrivate.h>

#include <QIdentityProxyModel>
#include <QSet>

#include <functional>

class QMODERNGRIDS_LIBRARY_API QmgDataModelDecorator : public QIdentityProxyModel
{
public:
   typedef std::function<QVariant(const QModelIndex &, int)> Handler;
   typedef std::function<QVariant(const QModelIndex &, int, std::function<QVariant()>)> RawHandler;
   typedef std::function<QVariant(const QModelIndex &, int, std::function<QVariant(int)>)> RawRoleHandler;

public:
   QmgDataModelDecorator(Handler handler, QObject *parent = nullptr);
   QmgDataModelDecorator(RawHandler handler, QObject *parent = nullptr);
   QmgDataModelDecorator(RawRoleHandler handler, QObject *parent = nullptr);
   QmgDataModelDecorator(const QSet<int> &roleExcludes, Handler handler, QObject *parent = nullptr);
   QmgDataModelDecorator(const QSet<int> &roleExcludes, RawHandler handler, QObject *parent = nullptr);
   QmgDataModelDecorator(const QSet<int> &roleExcludes, RawRoleHandler handler, QObject *parent = nullptr);
   virtual QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;

private:
   Handler m_handler;
   RawHandler m_rawHandler;
   RawRoleHandler m_rawRoleHandler;
   QSet<int> m_excludeRoles;
};

class QMODERNGRIDS_LIBRARY_API QmgColumnBasedDataModelDecorator : public QmgDataModelDecorator
{
public:
   QmgColumnBasedDataModelDecorator(int column, Handler handler, QObject *parent = nullptr);
   QmgColumnBasedDataModelDecorator(int column, const QSet<int> &roleExcludes, Handler handler, QObject *parent = nullptr);
   QmgColumnBasedDataModelDecorator(int column, RawHandler handler, QObject *parent = nullptr);
   QmgColumnBasedDataModelDecorator(int column, const QSet<int> &roleExcludes, RawHandler handler, QObject *parent = nullptr);
   QmgColumnBasedDataModelDecorator(int column, RawRoleHandler handler, QObject *parent = nullptr);
   QmgColumnBasedDataModelDecorator(int column, const QSet<int> &roleExcludes, RawRoleHandler handler, QObject *parent = nullptr);
   virtual QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;

private:
   int m_column;
};

class QMODERNGRIDS_LIBRARY_API QmgRoleBasedDataModelDecorator : public QmgDataModelDecorator
{
public:
   QmgRoleBasedDataModelDecorator(int role, Handler handler, QObject *parent = nullptr);
   QmgRoleBasedDataModelDecorator(int role, RawHandler handler, QObject *parent = nullptr);
   QmgRoleBasedDataModelDecorator(int role, RawRoleHandler handler, QObject *parent = nullptr);
   virtual QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;

private:
   int m_role;
};

class QMODERNGRIDS_LIBRARY_API QmgColumnAndRoleBasedDataModelDecorator : public QmgDataModelDecorator
{
public:
   QmgColumnAndRoleBasedDataModelDecorator(int column, int role, Handler handler, QObject *parent = nullptr);
   QmgColumnAndRoleBasedDataModelDecorator(int column, int role, RawHandler handler, QObject *parent = nullptr);
   QmgColumnAndRoleBasedDataModelDecorator(int column, int role, RawRoleHandler handler, QObject *parent = nullptr);
   virtual QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;

private:
   int m_column;
   int m_role;
};
