#include "jmarket.h"
#include <QDebug>
#include <QDateTime>

JMarket::JMarket()
{

}

JMarket::JMarket(QString _marketCurrency, QString _baseCurrency, QString _marketCurrencyLong, QString _baseCurrencyLong, double _minTradeSize, QString _marketName, bool _isActive, QString _created)
{
	marketCurrency_ = _marketCurrency;
	baseCurrency_ = _baseCurrency;
	marketCurrencyLong_ = _marketCurrencyLong;
	baseCurrencyLong_ = _baseCurrencyLong;
	minTradeSize_ = _minTradeSize;
	marketName_ = _marketName;
	isActive_ = _isActive;
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

