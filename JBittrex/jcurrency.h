#ifndef JCURRENCY_H
#define JCURRENCY_H

#include <QString>

class JCurrency
{
private:
	QString currency_;
	QString currencyLong_;
	bool isActive_ = false;
public:
	JCurrency();
	JCurrency(QString _currency, QString _currencyLong, bool _isActive = false);

	QString getCurrency(){ return currency_;	};
	QString getCurrencyLong(){ return currencyLong_;	};
	bool getIsActive(){ return isActive_;	};
};

#endif // JCURRENCY_H
