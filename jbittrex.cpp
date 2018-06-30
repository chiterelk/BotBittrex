#include "jbittrex.h"
#include <QDebug>
#include <QJsonDocument>
#include <QJsonArray>
#include <QJsonObject>
#include <QDateTime>
#include <QByteArray>
#include <QMessageAuthenticationCode>
#include <QCryptographicHash>
#include <QDateTime>



JBittrex::JBittrex(QObject *parent) : QObject(parent)
{
	connect(NAManager_,&QNetworkAccessManager::finished,this,&JBittrex::gotReply);
}
void JBittrex::getTickers()
{
	pingGetTickers_.start();
	NAManager_->get(QNetworkRequest(QUrl("https://bittrex.com/api/v1.1/public/getmarketsummaries")));
}

void JBittrex::getMarkets()
{
	pingGetMarkets_.start();
	NAManager_->get(QNetworkRequest(QUrl("https://bittrex.com/api/v1.1/public/getmarkets")));
}

void JBittrex::getCurrencies()
{
	pingGetCurrencies_.start();
	NAManager_->get(QNetworkRequest(QUrl("https://bittrex.com/api/v1.1/public/getcurrencies")));
}

void JBittrex::getWallet(QString _apiKey, QString _secretKey)
{
	QByteArray uri = "https://bittrex.com/api/v1.1/account/getbalances?apikey="+_apiKey.toUtf8()+"&nonce=" + QString::number(QDateTime::currentDateTime().toTime_t()).toUtf8();
	QMessageAuthenticationCode code(QCryptographicHash::Sha512);
	code.setKey(_secretKey.toUtf8());
	code.addData(uri);
	QNetworkRequest request;
	request.setUrl(QUrl(uri));
	request.setHeader(QNetworkRequest::ContentTypeHeader,"application/json");
	request.setRawHeader("apisign",code.result().toHex());
	pingGetBalances_.start();
	NAManager_->get(request);
}
void JBittrex::openBuyOrder(QString _apiKey, QString _secretKey,QString _market, double _quantity, double _rate)
{
	QByteArray uri = "https://bittrex.com/api/v1.1/market/buylimit?apikey="+_apiKey.toUtf8()+"&market=" + _market.toUtf8() +"&nonce=" + QString::number(QDateTime::currentDateTime().toTime_t()).toUtf8()+"&quantity=" + QString::number(_quantity,'f',8).toUtf8() +"&rate="+QString::number(_rate,'f',8).toUtf8();
	QMessageAuthenticationCode code(QCryptographicHash::Sha512);
	code.setKey(_secretKey.toUtf8());
	code.addData(uri);
	QNetworkRequest request;
	request.setUrl(QUrl(uri));
	request.setHeader(QNetworkRequest::ContentTypeHeader,"application/json");
	request.setRawHeader("apisign",code.result().toHex());
	pingOpenBuyOrder_.start();
	NAManager_->get(request);
}

void JBittrex::openSellOrder(QString _apiKey, QString _secretKey,QString _market, double _quantity, double _rate)
{
	QByteArray uri = "https://bittrex.com/api/v1.1/market/selllimit?apikey="+_apiKey.toUtf8()+"&market=" + _market.toUtf8() +"&nonce=" + QString::number(QDateTime::currentDateTime().toTime_t()).toUtf8()+"&quantity=" + QString::number(_quantity,'f',8).toUtf8() +"&rate="+QString::number(_rate,'f',8).toUtf8();
	QMessageAuthenticationCode code(QCryptographicHash::Sha512);
	code.setKey(_secretKey.toUtf8());
	code.addData(uri);
	QNetworkRequest request;
	request.setUrl(QUrl(uri));
	request.setHeader(QNetworkRequest::ContentTypeHeader,"application/json");
	request.setRawHeader("apisign",code.result().toHex());
	pingOpenSellOrder_.start();
	NAManager_->get(request);
}

void JBittrex::cancelOrder(QString _apiKey, QString _secretKey, QString _uuid)
{
	QByteArray uri = "https://bittrex.com/api/v1.1/market/cancel?apikey="+_apiKey.toUtf8()+"&uuid="+_uuid.toUtf8()+"&nonce=" + QString::number(QDateTime::currentDateTime().toTime_t()).toUtf8();
	QMessageAuthenticationCode code(QCryptographicHash::Sha512);
	code.setKey(_secretKey.toUtf8());
	code.addData(uri);
	QNetworkRequest request;
	request.setUrl(QUrl(uri));
	request.setHeader(QNetworkRequest::ContentTypeHeader,"application/json");
	request.setRawHeader("apisign",code.result().toHex());
	pingCancelOrde_.start();
	NAManager_->get(request);
}

void JBittrex::getOpenOrders(QString _apiKey, QString _secretKey)
{
	QByteArray uri = "https://bittrex.com/api/v1.1/market/getopenorders?apikey="+_apiKey.toUtf8()+"&nonce=" + QString::number(QDateTime::currentDateTime().toTime_t()).toUtf8();
	QMessageAuthenticationCode code(QCryptographicHash::Sha512);
	code.setKey(_secretKey.toUtf8());
	code.addData(uri);
	QNetworkRequest request;
	request.setUrl(QUrl(uri));
	request.setHeader(QNetworkRequest::ContentTypeHeader,"application/json");
	request.setRawHeader("apisign",code.result().toHex());
	pingGetOpenOrders_.start();
	NAManager_->get(request);
}



void JBittrex::gotReply(QNetworkReply *reply)//прием и обработка данных.
{
	QString url = reply->url().toString();
	qDebug()<< url;
	if(!reply->error())
	{
		if(url.indexOf("https://bittrex.com/api/v1.1/public/getmarkets") >= 0)
		{
			if(url.indexOf("https://bittrex.com/api/v1.1/public/getmarketsummaries") >= 0)//получение котировок
			{
				//qDebug()<<"1";
				emit ping(pingGetTickers_.elapsed());
				if(!reply->error())
				{
					QJsonDocument documment = QJsonDocument::fromJson(reply->readAll());
					QJsonObject root = documment.object();
					if(root.value("success").toBool())
					{
						if(root.value("result").isArray())
						{
							QList <JTickers> tickers;
							QJsonArray result = root.value("result").toArray();
							for(int i = 0; i<result.count();i++)
							{
								QJsonObject n = result.at(i).toObject();
								tickers << JTickers(n.value("MarketName").toString(),n.value("Ask").toDouble(),n.value("Bid").toDouble(),n.value("BaseVolume").toDouble());
								tickers.back().setCreated(n.value("Created").toString());
								tickers.back().setPrevDay(n.value("PrevDay").toDouble());
							}
							emit gotTickers(tickers);
						}else{
							qDebug()<<"Result is not array";
						}
					}else{
						qDebug()<<"Success is false";
					}
				}else{
					qDebug()<<"Error!";
				}
			}else{
				//qDebug()<<"2";
				emit ping(pingGetMarkets_.elapsed());
				if(!reply->error())
				{
					QJsonDocument documment = QJsonDocument::fromJson(reply->readAll());
					QJsonObject root = documment.object();

					if(root.value("success").toBool() == true)
					{

						if(root.value("result").isArray())
						{
							QJsonArray result = root.value("result").toArray();
							QList <JMarket> markets;
							for(int i = 0; i < result.count();i++)
							{
								QJsonObject n = result.at(i).toObject();
								markets << JMarket(n.value("MarketCurrency").toString(), n.value("BaseCurrency").toString(),
											n.value("MarketCurrencyLong").toString(),n.value("BaseCurrencyLong").toString(),n.value("MinTradeSize").toDouble(),
											n.value("MarketName").toString(),n.value("IsActive").toBool(),n.value("Created").toString());
//								markets.at(i).setMarketCurrency(n.value("MarketCurrency").toString());
//								markets.at(i).setBaseCurrency(n.value("BaseCurrency").toString());
//								markets.at(i).setMarketCurrencyLong(n.value("MarketCurrencyLong").toString());
//								markets.at(i).setBaseCurrencyLong(n.value("BaseCurrencyLong").toString());
//								markets.at(i).setMinTradeSize(n.value("MinTradeSize").toDouble());
//								markets.at(i).setMarketName(n.value("MarketName").toString());
//								markets.at(i).setIsActive(n.value("IsActive").toBool());
//								markets.at(i).setCreated(n.value("Created").toString());
							}
							emit gotMarkets(markets);
						}else{
							qDebug()<<"Result is not array";
						}
					}else{
						qDebug()<<"Success is false";
					}

				}else{
					qDebug()<<"Error!";
				}
			}
		}
		if(url.indexOf("https://bittrex.com/api/v1.1/public/getcurrencies") >= 0)
		{
			qDebug()<<"3";
			emit ping(pingGetCurrencies_.elapsed());
			if(!reply->error())
			{
				QJsonDocument documment = QJsonDocument::fromJson(reply->readAll());
				QJsonObject root = documment.object();

				if(root.value("success").toBool() == true)
				{

					if(root.value("result").isArray())
					{
						QJsonArray result = root.value("result").toArray();
						QList <JCurrency> currencies;
						for(int i = 0; i < result.count();i++)
						{
							QJsonObject n = result.at(i).toObject();
							currencies << JCurrency(n.value("Currency").toString(),n.value("CurrencyLong").toString(),n.value("IsActive").toBool());
						}
						emit gotCurrencies(currencies);
					}else{
						qDebug()<<"Result is not array";
					}
				}else{
					qDebug()<<"Success is false";
				}

			}else{
				qDebug()<<"Error!";
			}
		}
		if(url.indexOf("https://bittrex.com/api/v1.1/account/getbalances") >= 0)
		{
			emit ping(pingGetBalances_.elapsed());
			if(!reply->error())
			{
				QJsonDocument documment = QJsonDocument::fromJson(reply->readAll());
				QJsonObject root = documment.object();

				if(root.value("success").toBool() == true)
				{

					if(root.value("result").isArray())
					{
						QJsonArray result = root.value("result").toArray();
						QList <JBalance> wallet;
						for(int i = 0; i < result.count();i++)
						{
							QJsonObject n = result.at(i).toObject();
							wallet << JBalance(n.value("Currency").toString(),n.value("Balance").toDouble(),n.value("Available").toDouble());
						}
						emit gotWallet(wallet);
						if(!wallet.isEmpty())
						{
							wallet.clear();
						}
					}else{
						qDebug()<<"Result is not array";
					}
				}else{

					qDebug()<<"Success is false";
					emit successWalletIsFalse();

				}

			}else{
				qDebug()<<"Error!";
			}
		}
		if(url.indexOf("https://bittrex.com/api/v1.1/market/buylimit") >= 0)
		{
			emit ping(pingOpenBuyOrder_.elapsed());
			if(!reply->error())
			{
				QJsonDocument documment = QJsonDocument::fromJson(reply->readAll());
				QJsonObject root = documment.object();

				if(root.value("success").toBool() == true)
				{
					emit openedBuyOrder(root.value("result").toObject().value("uuid").toString());
				}else{
					qDebug()<<"Success is false";
					qDebug()<<"message: "<<root.value("message").toString();
				}

			}else{
				qDebug()<<"Error!";
			}
		}
		if(url.indexOf("https://bittrex.com/api/v1.1/market/selllimit") >= 0)
		{
			emit ping(pingOpenSellOrder_.elapsed());
			if(!reply->error())
			{
				QJsonDocument documment = QJsonDocument::fromJson(reply->readAll());
				QJsonObject root = documment.object();

				if(root.value("success").toBool() == true)
				{
					emit openedSellOrder(root.value("result").toObject().value("uuid").toString());
				}else{
					qDebug()<<"Success is false";
					qDebug()<<"message: "<<root.value("message").toString();
				}

			}else{
				qDebug()<<"Error!";
			}
		}
		if(url.indexOf("https://bittrex.com/api/v1.1/market/getopenorders") >= 0)
		{
			emit ping(pingGetOpenOrders_.elapsed());
			if(!reply->error())
			{
				QJsonDocument documment = QJsonDocument::fromJson(reply->readAll());
				QJsonObject root = documment.object();

				if(root.value("success").toBool() == true)
				{

					if(root.value("result").isArray())
					{
						QJsonArray result = root.value("result").toArray();
						QList <JOpenedOrder> openedOrders;
						for(int i = 0; i < result.count();i++)
						{
							QJsonObject n = result.at(i).toObject();
							openedOrders << JOpenedOrder(n.value("OrderUuid").toString(), n.value("Exchenge").toString(), n.value("OrderType").toString(),
																  n.value("Quantity").toDouble(), n.value("QuantityRemaining").toDouble(), n.value("Limit").toDouble());
//							openedOrders.at(i).setOrderUuid(n.value("OrderUuid").toString());
//							openedOrders.at(i).setExchange(n.value("Exchenge").toString());
//							openedOrders.at(i).setOrderType(n.value("OrderType").toString());
//							openedOrders.at(i).setQuantity(n.value("Quantity").toDouble());
//							openedOrders.at(i).setQuantityRemaining(n.value("QuantityRemaining").toDouble());
//							openedOrders.at(i).setLimit(n.value("Limit").toDouble());
						}
						emit gotOpenOrders(openedOrders);
					}else{
						qDebug()<<"Result is not array";
					}
				}else{
					qDebug()<<"Success is false";
				}

			}else{
				qDebug()<<"Error!";
			}
		}
		if(url.indexOf("https://bittrex.com/api/v1.1/market/cancel") >= 0)
		{
			emit ping(pingCancelOrde_.elapsed());
			if(!reply->error())
			{
				QJsonDocument documment = QJsonDocument::fromJson(reply->readAll());
				QJsonObject root = documment.object();

				if(root.value("success").toBool() == true)
				{
					emit canceledOrder();
				}
			}else
			{
				qDebug()<<"Error!";
			}
		}
	}else{
		qDebug()<<reply->errorString();
	}
	reply->deleteLater();
}



