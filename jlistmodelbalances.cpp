#include "jlistmodelbalances.h"

JListModelBalances::JListModelBalances(QObject *parent) :
	QAbstractListModel(parent)
{

}

int JListModelBalances::rowCount(const QModelIndex &parent) const
{
	return wallet.count();
}

int JListModelBalances::columnCount(const QModelIndex &parent) const
{
	if(wallet.isEmpty())
		return 0;
	else
		return 3;
}

QVariant JListModelBalances::data(const QModelIndex &index, int role) const
{
	if(!index.isValid())
	{
		return QVariant();
	}
	int row = index.row();
	int column = index.column();


	switch(column){
	case 0:
		switch(role)
		{
		case Qt::DisplayRole:
			return wallet.at(row)->getCurrency();
		case Qt::EditRole:
			return wallet.at(row)->getCurrency();
		case Qt::TextAlignmentRole:
			return Qt::AlignCenter;
		case Qt::BackgroundColorRole:
			if(wallet.at(row)->getCurrency()=="ETH" || wallet.at(row)->getCurrency()=="BTC" || wallet.at(row)->getCurrency()=="USDT")
			{
				return QBrush(QColor("#F2F2F2"));
			}
		default:
			return QVariant();
		}
	case 1:
		switch(role)
		{
		case Qt::DisplayRole:
			return QString::number(wallet.at(row)->getBalance(),'f',8);
		case Qt::EditRole:
			return QString::number(wallet.at(row)->getBalance(),'f',8);
		case Qt::TextAlignmentRole:
			return Qt::AlignCenter;
		case Qt::BackgroundColorRole:
			if(wallet.at(row)->getCurrency()=="ETH" || wallet.at(row)->getCurrency()=="BTC" || wallet.at(row)->getCurrency()=="USDT")
			{
				return QBrush(QColor("#F2F2F2"));
			}
		default:
			return QVariant();
		}
	case 2:
		switch(role)
		{
		case Qt::DisplayRole:
			return QString::number(wallet.at(row)->getAvailable(),'f',8);
		case Qt::EditRole:
			return QString::number(wallet.at(row)->getAvailable(),'f',8);
		case Qt::TextAlignmentRole:
			return Qt::AlignCenter;
		case Qt::BackgroundColorRole:
			if(wallet.at(row)->getCurrency()=="ETH" || wallet.at(row)->getCurrency()=="BTC" || wallet.at(row)->getCurrency()=="USDT")
			{
				return QBrush(QColor("#F2F2F2"));
			}
		default:
			return QVariant();
		}
		default:

			return QVariant();
		}

}
Qt::ItemFlags JListModelBalances::flags(const QModelIndex &index) const
{
	if(!index.isValid())
	{
		return Qt::NoItemFlags;
	}
	return Qt::ItemIsEnabled | Qt::ItemIsEditable;
}

void JListModelBalances::setBalances(QList<JBalance *> _wallet)
{
	if(!wallet.isEmpty())
		wallet.clear();
	wallet = _wallet;
	if(!_wallet.isEmpty())
		_wallet.clear();
	emit layoutChanged();
}
QVariant JListModelBalances::headerData(int section, Qt::Orientation orientation, int role) const
{
	switch(role)
	{
	case Qt::DisplayRole:
		switch(section)
		{
		case 0:
			return QString("Name");
		case 1:
			return QString("Total");
		case 2:
			return QString("Available");
		}
	default:
			return QVariant();
	}

}
