#ifndef JMARKET_H
#define JMARKET_H

#include <QString>


class JMarket
{
private:
	QString marketCurrency_;
	QString baseCurrency_;
	QString marketCurrencyLong_;
	QString baseCurrencyLong_;
	double minTradeSize_;
	QString marketName_;
	bool isActive_ = false;
	QString created_;
	uint createdUNIX_ = 0;
public:
	JMarket();
	JMarket(QString _marketCurrency, QString _baseCurrency, QString _marketCurrencyLong, QString _baseCurrencyLong, double _minTradeSize, QString _marketName, bool _isActive, QString _created);
	void setMarketCurrency(const QString _marketCurrency ){	marketCurrency_ = _marketCurrency;	};
	void setBaseCurrency(QString _baseCurrency){	baseCurrency_ = _baseCurrency;	};
	void setMarketCurrencyLong(QString _marketCurrencyLong){	marketCurrencyLong_ = _marketCurrencyLong;	};
	void setBaseCurrencyLong(QString _baseCurrencyLong){	baseCurrencyLong_ = _baseCurrencyLong;	};
	void setMinTradeSize(double _minTradeSize){	minTradeSize_ = _minTradeSize; };
	void setMarketName(QString _marketName){	marketName_ = _marketName;	};
	void setIsActive(bool _isActive){	isActive_ = _isActive;	};
	void setCreated(QString _created);


	QString getMarketCurrency() const {	return marketCurrency_;	};
	QString getBaseCurrency() const {	return baseCurrency_;	};
	QString getMarketCurrencyLong() const {	return marketCurrencyLong_;	};
	QString getBaseCurrencyLong() const {	return baseCurrencyLong_;	};
	double getMinTradeSize() const {	return minTradeSize_;	};
	QString getMarketName() const {	return marketName_;	};
	bool getIsActive() const {	return isActive_;	};
	QString getCreated() const {	return created_;	};
	uint getCreatedUNIX() const {	return createdUNIX_;	};

};


#endif // JMARKET_H
