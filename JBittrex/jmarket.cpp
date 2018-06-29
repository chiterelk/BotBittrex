#include "jmarket.h"
#include <QDebug>
#include <QDateTime>

JMarket::JMarket()
{

}

void JMarket::setCreated(QString _created)//Сохраняю дату листинга монеты и перевожу ее в UNIX_TIME
//Монеты которые добавили недаво могут находиться в пампе, из-за этого с ними торговать не буду.
{
	created_ = _created;
	bool newFormat = false;
	for(int i = 0;i<created_.count();i++)
		if(created_.at(i)==QChar('.'))
			newFormat = true;

	if(newFormat)
	{
		createdUNIX_ = QDateTime::fromString(created_,"yyyy-MM-dd'T'HH:mm:ss.z").toTime_t();
	}else
	{
		createdUNIX_ = QDateTime::fromString(created_,"yyyy-MM-dd'T'HH:mm:ss").toTime_t();
	}
}

