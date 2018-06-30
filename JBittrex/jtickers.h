#ifndef JTICKERS_H
#define JTICKERS_H
#include <QString>

class JTickers
{
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
	JTickers(QString _marketName, double _ask, double _bid, double _baseVolume);
	JTickers();
	void setAsk(double _ask){	ask_ = _ask;	};
	void setBid(double _bid){	bid_ = _bid;	};
	void setMarketName(QString _marketName){	marketName_ = _marketName;	};
	void setCreated(QString _created);
	void setPrevDay(double _prevDay);

	double getAsk(void) const {	return ask_;	};
	double getBid(void) const {	return bid_;	};
	double getSpread(void) const {	return spread_;	};
	double getRank(void) const {	return rank_;	};
	QString getMarketName(void) const {	return marketName_;	};
	double getBaseVolume() const { return baseVolume_; };
	QString getBaseCurrency() const {	return baseCurrency_;	};
	QString getCreated() const {	return created_;	};
	uint getCreatedUNIX() const {	return createdUNIX_;	};
	uint hawOld() const ;
	double getPrevDay() const {	return prevDay_;};
	double getPercentUp() const {	return percentUp_;};
};

#endif // JTICKERS_H
