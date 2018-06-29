#ifndef JLISTMODELEVENTS_H
#define JLISTMODELEVENTS_H

#include <QObject>
#include <QAbstractListModel>

class JListModelEvents : public QAbstractListModel
{
	Q_OBJECT
public:
	explicit JListModelEvents(QObject * parent = 0);
	int rowCount(const QModelIndex &parent) const;
	QVariant data(const QModelIndex &index, int role) const;
	Qt::ItemFlags flags(const QModelIndex &index) const;
	void addEvent(QString _event);
private:
	QList <QString> events;
};

#endif // JLISTMODELEVENTS_H
