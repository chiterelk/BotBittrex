#include "jlistmodelevents.h"

JListModelEvents::JListModelEvents(QObject *parent) :
	QAbstractListModel(parent)
{

}

int JListModelEvents::rowCount(const QModelIndex &parent) const
{
	return events.count();
}

QVariant JListModelEvents::data(const QModelIndex &index, int role) const
{
	if(!index.isValid())
	{
		return QVariant();
	}
	int row = index.row();
	switch(role)
	{
	case Qt::DisplayRole:
		return events.at(row);
	case Qt::EditRole:
		return events.at(row);
	case Qt::TextAlignmentRole:
		return Qt::AlignLeft;
	default:
		return QVariant();
	}
}

Qt::ItemFlags JListModelEvents::flags(const QModelIndex &index) const
{
	if(!index.isValid())
	{
		return Qt::NoItemFlags;
	}
	return Qt::ItemIsEnabled | Qt::ItemIsEditable;
}

void JListModelEvents::addEvent(QString _event)
{
	events<<_event;
	emit layoutChanged();
}
