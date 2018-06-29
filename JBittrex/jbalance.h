#ifndef JBALANCE_H
#define JBALANCE_H

#include <QObject>

class JBalance : public QObject
{
	Q_OBJECT
private:
	QString currency_;
	double balance_ = 0;
	double available_ = 0;
public:
	explicit JBalance(QObject *parent = nullptr);
	JBalance();
	JBalance(QString _currency, double _balance, double _available);

signals:

public slots:
	double getBalance(){	return balance_;	};
	double getAvailable(){	return available_;	};
	QString getCurrency(){	return currency_;	};

	void setBalance(double _balance){	balance_ = _balance;	};
	void setAvailable(double _available){	available_ = _available;	};
	void setCurrency(QString _currency){	currency_ = _currency;	};
};

#endif // JBALANCE_H
