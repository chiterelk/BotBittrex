#ifndef JLISTMODELBALANCES_H
#define JLISTMODELBALANCES_H

#include <QObject>
#include <QAbstractListModel>
#include <QBrush>
#include <QList>
#include "JBittrex/jbalance.h"

class JListModelBalances : public QAbstractListModel
{
	Q_OBJECT
public:
	explicit JListModelBalances(QObject * parent = 0);
	int rowCount(const QModelIndex &parent) const;
	int columnCount(const QModelIndex &parent) const;
	QVariant data(const QModelIndex &index, int role) const;
	Qt::ItemFlags flags(const QModelIndex &index) const;
	void setBalances(QList <JBalance*> _wallet);
	QVariant headerData(int section, Qt::Orientation orientation, int role) const;
private:
	QList <JBalance*> wallet;
};

#endif // JLISTMODELBALANCES_H
