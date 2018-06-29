#ifndef JTICKERS_H
#define JTICKERS_H

#include <QObject>

class JTickers : public QObject
{
	Q_OBJECT
private:
	double ask_ = 0;
	double bid_ = 0;
	double baseVolume_ = 0;
	QString marketName_;
	double spread_;
	double rank_;
	QString baseCurrency_;
	QString created_;
	uint createdUNIX_ = 0;
	double prevDay_ = 0;
	double percentUp_ = 0;//как виросла валюта за день.

	public:
	explicit JTickers(QObject *parent = nullptr);
	JTickers(QString _marketName, double _ask, double _bid, double _baseVolume);
	void setAsk(double _ask){	ask_ = _ask;	};
	void setBid(double _bid){	bid_ = _bid;	};
	void setMarketName(QString _marketName){	marketName_ = _marketName;	};
	void setCreated(QString _created);
	void setPrevDay(double _prevDay);

	double getAsk(void){	return ask_;	};
	double getBid(void){	return bid_;	};
	double getSpread(void){	return spread_;	};
	double getRank(void){	return rank_;	};
	QString getMarketName(void){	return marketName_;	};
	double getBaseVolume(){ return baseVolume_; };
	QString getBaseCurrency(){	return baseCurrency_;	};
	QString getCreated(){	return created_;	};
	uint getCreatedUNIX(){	return createdUNIX_;	};
	uint hawOld();
	double getPrevDay(){	return prevDay_;};
	double getPercentUp(){	return percentUp_;};

signals:

public slots:
};

#endif // JTICKERS_H
