#include "jcurrency.h"

JCurrency::JCurrency()
{

}

JCurrency::JCurrency(QString _currency, QString _currencyLong, bool _isActive)
{
	currency_ = _currency;
	currencyLong_ = _currencyLong;
	isActive_ = _isActive;
}
