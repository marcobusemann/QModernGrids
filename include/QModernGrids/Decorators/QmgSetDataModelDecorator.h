
#pragma once

#include <QModernGrids/QmgPrivate.h>

#include <QIdentityProxyModel>
#include <QSet>

#include <functional>

class QMODERNGRIDS_LIBRARY_API QmgSetDataModelDecorator : public QIdentityProxyModel
{
public:
   typedef std::function<bool(const QModelIndex &, const QVariant &)> Handler;

public:
   QmgSetDataModelDecorator(Handler handler, QObject *parent = nullptr);
   QmgSetDataModelDecorator(const QSet<int> &roleExcludes, Handler handler, QObject *parent = nullptr);
   virtual bool setData(const QModelIndex &index, const QVariant &value, int role = Qt::EditRole) override;

private:
   Handler m_handler;
   QSet<int> m_excludeRoles;
};

class QMODERNGRIDS_LIBRARY_API QmgColumnBasedSetDataModelDecorator : public QmgSetDataModelDecorator
{
public:
   QmgColumnBasedSetDataModelDecorator(int column, Handler handler, QObject *parent = nullptr);
   QmgColumnBasedSetDataModelDecorator(int column, const QSet<int> &roleExcludes, Handler handler, QObject *parent = nullptr);
   virtual bool setData(const QModelIndex &index, const QVariant &value, int role = Qt::EditRole) override;

private:
   int m_column;
};

class QMODERNGRIDS_LIBRARY_API QmgRoleBasedSetDataModelDecorator : public QmgSetDataModelDecorator
{
public:
   QmgRoleBasedSetDataModelDecorator(int role, Handler handler, QObject *parent = nullptr);
   virtual bool setData(const QModelIndex &index, const QVariant &value, int role = Qt::EditRole) override;

private:
   int m_role;
};

class QMODERNGRIDS_LIBRARY_API QmgColumnAndRoleBasedSetDataModelDecorator : public QmgSetDataModelDecorator
{
public:
   QmgColumnAndRoleBasedSetDataModelDecorator(int column, int role, Handler handler, QObject *parent = nullptr);
   virtual bool setData(const QModelIndex &index, const QVariant &value, int role = Qt::EditRole) override;

private:
   int m_column;
   int m_role;
};
