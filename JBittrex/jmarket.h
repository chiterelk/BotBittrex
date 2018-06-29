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
	void setMarketCurrency(QString _marketCurrency){	QString marketCurrency_ = _marketCurrency;	};
	void setBaseCurrency(QString _baseCurrency){	baseCurrency_ = _baseCurrency;	};
	void setMarketCurrencyLong(QString _marketCurrencyLong){	marketCurrencyLong_ = _marketCurrencyLong;	};
	void setBaseCurrencyLong(QString _baseCurrencyLong){	baseCurrencyLong_ = _baseCurrencyLong;	};
	void setMinTradeSize(double _minTradeSize){	minTradeSize_ = _minTradeSize; };
	void setMarketName(QString _marketName){	marketName_ = _marketName;	};
	void setIsActive(bool _isActive){	isActive_ = _isActive;	};
	void setCreated(QString _created);


	QString getMarketCurrency(){	return marketCurrency_;	};
	QString getBaseCurrency(){	return baseCurrency_;	};
	QString getMarketCurrencyLong(){	return marketCurrencyLong_;	};
	QString getBaseCurrencyLong(){	return baseCurrencyLong_;	};
	double getMinTradeSize(){	return minTradeSize_;	};
	QString getMarketName(){	return marketName_;	};
	bool getIsActive(){	return isActive_;	};
	QString getCreated(){	return created_;	};
	uint getCreatedUNIX(){	return createdUNIX_;	};

};


#endif // JMARKET_H
