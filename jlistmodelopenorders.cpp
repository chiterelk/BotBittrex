#include "jlistmodelopenorders.h"
#include "QDebug"

JListModelOpenOrder::JListModelOpenOrder(QObject *parent) :
	QAbstractListModel(parent)
{

}

int JListModelOpenOrder::rowCount(const QModelIndex &parent) const
{
	return listId.count();
}

int JListModelOpenOrder::columnCount(const QModelIndex &parent) const
{
	if(listId.count())
		return 3;
	return 0;
}

QVariant JListModelOpenOrder::data(const QModelIndex &index, int role) const
{
	if(!index.isValid())
		return QVariant();

	int row = index.row();
	int column = index.column();
	switch(column){
	case 0:
		switch(role)
		{
		case Qt::DisplayRole:
			return listId.at(row);
		case Qt::EditRole:
			return listId.at(row);
		case Qt::TextAlignmentRole:
			return Qt::AlignCenter;
		case Qt::BackgroundColorRole:
			if(listType.at(row)=="Sell")
			{
				return QBrush(QColor("#EAC4C4"));
			}else{
				return QBrush(QColor("#BBD9ED"));
			}
		default:
			return QVariant();
		}
	case 1:
		switch(role)
		{
		case Qt::DisplayRole:
			return listPrice.at(row);
		case Qt::TextAlignmentRole:
			return Qt::AlignCenter;
		case Qt::BackgroundColorRole:
			if(listType.at(row)=="Sell")
			{
				return QBrush(QColor("#EAC4C4"));
			}else{
				return QBrush(QColor("#BBD9ED"));
			}
		default:
			return QVariant();
		}
	case 2:
		switch(role)
		{
		case Qt::DisplayRole:
			return listQuantity.at(row);
		case Qt::TextAlignmentRole:
			return Qt::AlignCenter;
		case Qt::BackgroundColorRole:
			if(listType.at(row)=="Sell")
			{
				return QBrush(QColor("#EAC4C4"));
			}else{
				return QBrush(QColor("#BBD9ED"));
			}
		default:
			return QVariant();
		}
	}
}
Qt::ItemFlags JListModelOpenOrder::flags(const QModelIndex &index) const
{
	if(!index.isValid())
	{
		return Qt::NoItemFlags;
	}
	return Qt::ItemIsEnabled | Qt::ItemIsSelectable;
}

QVariant JListModelOpenOrder::headerData(int section, Qt::Orientation orientation, int role) const
{
	switch(role)
	{
	case Qt::DisplayRole:
		switch(section)
		{
		case 0:
			return QString("Id");
		case 1:
			return QString("Prace");
		case 2:
			return QString("Quantity");
		}
	default:
			return QVariant();
	}

}

void JListModelOpenOrder::addRow(QString _id, double _price, double _quantity, QString _type)
{
	listId << _id;
	listPrice << _price;
	listQuantity << _quantity;
	listType <<_type;
	emit layoutChanged();
}

void JListModelOpenOrder::clear()
{
	listId.clear();
	listPrice.clear();
	listQuantity.clear();
	listType.clear();
	emit layoutChanged();
}
