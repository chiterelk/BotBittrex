#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTimer>

#include "jbittrex.h"
#include <QList>
#include <JBittrex/jbalance.h>
#include "jlistmodelbalances.h"
#include "jlistmodelevents.h"
#include "jlistmodelopenorders.h"
#include "JBittrex/jtickers.h"
#include "jsellorder.h"

#include <QDateTime>

#include <QLabel>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
	Q_OBJECT

public:
	explicit MainWindow(QWidget *parent = 0);
	~MainWindow();

public slots:
	void successWalletIsFalse();
	void gotWalletFirstTime(QList<JBalance> _wallet);
	void gotWallet(QList<JBalance> _wallet);
	void gotTickers(QList <JTickers> _tickers);

	void showBalances(QList<JBalance> &_wallet);
	void showOrders();

	void gotMarkets(QList <JMarket> _markets);
	void openedBuyOrder(QString _uuid);
	void openedSellOrder(QString _uuid);
	void gotOpenOrders(QList <JOpenedOrder> _openedOrders);
	void canceledOrder();
	void mainProcess();
private slots:
	void on_pushButtonStart_clicked();
	void showProcess();
	void showPing(int ping);
	void getWallet();



	void on_checkBox_clicked(bool checked);

	void on_pushButton_clicked();

private:
	Ui::MainWindow *ui;

	QTimer *mainTimer;
	QTimer *walletTimer;


	JBittrex *bittrex;
	QList<JBalance> wallet;
	QList<JTickers> tickers;
	QList<JTickers> tickersShow;
	JListModelBalances * listModelBalances;
	JListModelEvents * listModelEvents;
	JListModelOpenOrder * listModelOpenedOrder;
	JTickers tickerSpread;
	QList <JSellOrder> buyOrders;
	QList <JOpenedOrder> openedBuyOrders;
	QList <JOpenedOrder> openedSellOrders;




	QString apiKey;
	QString secretKey;

	QString marketName;

	QString mainCurrency;
	double minSpread;
	double minProfit;
	double profit;
	double Deposit;
	double deposit;
	double perekritie;
	int numberOrders;
	double martingail;
	double perestanovka;

	int oldMounth;
	double minTradeSize;
	double minTradeSizeMainCurrency;

	double midPrice = 0;
	double summQuantity = 0;

	int process = 0;

	QLabel *labelProcess;
	QLabel *labelPing;

	QList <QString> badPairs;

};

#endif // MAINWINDOW_H
