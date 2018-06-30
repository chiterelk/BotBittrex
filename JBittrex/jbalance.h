#ifndef JBALANCE_H
#define JBALANCE_H

#include <QString>

class JBalance
{
private:
	QString currency_;
	double balance_ = 0;
	double available_ = 0;
public:
	JBalance(QString _currency, double _balance, double _available);
	double getBalance()const{	return balance_;	};
	double getAvailable()const{	return available_;	};
	QString getCurrency()const{	return currency_;	};

	void setBalance(double _balance){	balance_ = _balance;	};
	void setAvailable(double _available){	available_ = _available;	};
	void setCurrency(QString _currency){	currency_ = _currency;	};
};

#endif // JBALANCE_H
