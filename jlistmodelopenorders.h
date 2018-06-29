#ifndef JLISTMODELOPENORDERS_H
#define JLISTMODELOPENORDERS_H

#include <QObject>
#include <QAbstractListModel>
#include <QBrush>
#include <QList>
#include <QString>


class JListModelOpenOrder : public QAbstractListModel
{
	Q_OBJECT
public:
	explicit JListModelOpenOrder(QObject *parent = 0);

	int rowCount(const QModelIndex &parent) const;
	int columnCount(const QModelIndex &parent) const;
	QVariant data(const QModelIndex &index, int role) const;
	Qt::ItemFlags flags(const QModelIndex &index) const;
	QVariant headerData(int section, Qt::Orientation orientation, int role) const;

	void addRow(QString _id, double _price, double _quantity, QString _type);
	void clear();
private:
	QList <QString> listId;
	QList <double> listPrice;
	QList <double> listQuantity;
	QList <QString> listType;

};

#endif // JLISTMODELOPENORDERS_H
