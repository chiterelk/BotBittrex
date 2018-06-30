#ifndef JBITTREX_H
#define JBITTREX_H

#include <QObject>
#include <QList>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QList>
#include <QNetworkRequest>
#include <QUrl>
#include <QTime>

#include "JBittrex/jtickers.h"
#include "JBittrex/jbalance.h"
#include "JBittrex/jmarket.h"
#include "JBittrex/jcurrency.h"
#include "JBittrex/jopenedorder.h"


class JBittrex : public QObject
{
	Q_OBJECT
private:

	QNetworkAccessManager *NAManager_ = new QNetworkAccessManager(this);

	QTime pingGetTickers_;
	QTime pingGetBalances_;
	QTime pingGetMarkets_;
	QTime pingGetCurrencies_;
	QTime pingOpenBuyOrder_;
	QTime pingOpenSellOrder_;
	QTime pingGetOpenOrders_;
	QTime pingCancelOrde_;

public:
	explicit JBittrex(QObject *parent = nullptr);
	void getTickers();
	void getMarkets();
	void getWallet(QString _apiKey, QString _secretKey);
	void getCurrencies();
	void openBuyOrder(QString _apiKey, QString _secretKey, QString _market, double _quantity, double _rate);
	void openSellOrder(QString _apiKey, QString _secretKey, QString _market, double _quantity, double _rate);
	void cancelOrder(QString _apiKey, QString _secretKey, QString _uuid);
	void getOpenOrders(QString _apiKey, QString _secretKey);

signals:
	void ping(int _ping);
	void successWalletIsFalse();
	void gotTickers(QList <JTickers> _tickers);
	void gotWallet(QList <JBalance> _wallet);
	void gotMarkets(QList <JMarket> _markets);
	void gotCurrencies(QList <JCurrency> _markets);
	void openedBuyOrder(QString _uuid);
	void openedSellOrder(QString _uuid);
	void gotOpenOrders(QList <JOpenedOrder> _openedOrders);
	void canceledOrder();
private slots:



	void gotReply(QNetworkReply *reply);

};

#endif // JBITTREX_H
