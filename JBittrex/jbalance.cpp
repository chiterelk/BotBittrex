#include "jbalance.h"

JBalance::JBalance(QObject *parent) : QObject(parent)
{

}

JBalance::JBalance()
{

}

JBalance::JBalance(QString _currency, double _balance, double _available)
{
	currency_ = _currency;
	balance_ = _balance;
	available_ = _available;
}
