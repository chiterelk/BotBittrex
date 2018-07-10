#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>
#include <QDateTime>
#include <cmath>

MainWindow::MainWindow(QWidget *parent) :
	QMainWindow(parent),
	ui(new Ui::MainWindow)
{
	ui->setupUi(this);

	badPairs<<"BTC-DOGE";
	badPairs<<"BTC-ABY";
	badPairs<<"BTC-BITB";
	badPairs<<"BTC-XMY";
	badPairs<<"BTC-RDD";
	badPairs<<"BTC-2Give";
	badPairs<<"BTC-XDN";
	badPairs<<"BTC-MUSIK";
	badPairs<<"BTC-OCN";
	badPairs<<"BTC-FLDC";
	badPairs<<"BTC-SC";
	badPairs<<"BTC-PINC";
	badPairs<<"BTC-ADT";
	badPairs<<"BTC-BURST";
	badPairs<<"BTC-STORM";
	badPairs<<"BTC-VEE";
	badPairs<<"BTC-DOPE";
	badPairs<<"BTC-PTC";





	bittrex = new JBittrex(this);
	listModelBalances = new JListModelBalances(this);
	listModelEvents = new JListModelEvents(this);
	listModelOpenedOrder = new JListModelOpenOrder(this);
	mainTimer = new QTimer(this);
	walletTimer = new QTimer(this);
	connect(mainTimer,&QTimer::timeout,this,&MainWindow::mainProcess);
	connect(walletTimer,&QTimer::timeout,this,&MainWindow::getWallet);
	connect(bittrex,&JBittrex::ping,this,&MainWindow::showPing);
	connect(bittrex,&JBittrex::openedBuyOrder,this,&MainWindow::openedBuyOrder);
	connect(bittrex,&JBittrex::openedSellOrder,this,&MainWindow::openedSellOrder);
	connect(bittrex,&JBittrex::canceledOrder,this,&MainWindow::canceledOrder);
	connect(bittrex,&JBittrex::gotOpenOrders,this,&MainWindow::gotOpenOrders);
	connect(bittrex,&JBittrex::errorOpenBuyOreder,this,&MainWindow::errorOpenBuyOreder);
	connect(bittrex,&JBittrex::errorOpenSellOreder,this,&MainWindow::errorOpenSellOreder);
	connect(bittrex,&JBittrex::errorCancelOrder,this,&MainWindow::errorCancelOrder);


	connect(NAMTelegram,&QNetworkAccessManager::finished,this,&MainWindow::answerFromTelegram);
	walletTimer->start(10000);
	oldMounth = 3; //допускаются пары не моложе n месяцев

	ui->tableViewBalances->setModel(listModelBalances);
	ui->tableViewBalances->setColumnWidth(0,ui->tableViewBalances->width()/3);
	ui->tableViewBalances->setColumnWidth(1,ui->tableViewBalances->width()/3);
	ui->tableViewBalances->setColumnWidth(2,ui->tableViewBalances->width()/3);	
	ui->tableViewBalances->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);

	ui->listViewEvents->setModel(listModelEvents);
	ui->tableViewOpenedOrders->setModel(listModelOpenedOrder);
	ui->tableViewOpenedOrders->setColumnWidth(0,ui->tableViewBalances->width()/3);
	ui->tableViewOpenedOrders->setColumnWidth(1,ui->tableViewBalances->width()/3);
	ui->tableViewOpenedOrders->setColumnWidth(2,ui->tableViewBalances->width()/3);
	ui->tableViewOpenedOrders->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);

	labelProcess = new QLabel(this);
	labelPing = new QLabel(this);
	ui->statusBar->addWidget(labelProcess);
	ui->statusBar->addWidget(labelPing);

	ui->labelTryAgain->hide();
	ui->groupBoxPair->hide();
	ui->groupBoxEvents->hide();
	ui->groupBoxBalances->hide();
	ui->groupBoxOpenedOrders->hide();



}

MainWindow::~MainWindow()
{
	delete ui;
}


void MainWindow::on_pushButtonStart_clicked()
{
	apiKey = ui->lineEditApiKey->text().toLatin1();
	secretKey = ui->lineEditSecretKey->text().toLatin1();

	connect(bittrex,&JBittrex::gotWallet,this,&MainWindow::gotWalletFirstTime);
	connect(bittrex,&JBittrex::successWalletIsFalse,this,&MainWindow::successWalletIsFalse);
	connect(bittrex,&JBittrex::gotWallet,this,&MainWindow::gotWallet);

	bittrex->getWallet(apiKey,secretKey);
	ui->groupBoxStart->hide();
	mainCurrency = ui->comboBoxMainCurrency->currentText();
	minSpread = ui->lineEditMinSpread->text().toDouble();
	minProfit = ui->lineEditMinProfit->text().toDouble();
	deposit = ui->lineEditDeposit->text().toDouble();
	perekritie = ui->lineEditPerekritie->text().toDouble();
	numberOrders = ui->spinBoxNumberOrders->value();
	martingail = ui->lineEditMartingale->text().toDouble();
	perestanovka = ui->lineEditPerestanovka->text().toDouble();

	listModelEvents->addEvent(QDateTime::currentDateTime().toString("dd.MM.yyyy hh:mm:ss ")+"Бот запущен!");
	sendMesageToTelegram("Бот запущен!");
}

void MainWindow::showProcess()
{
	labelProcess->setText("Process: "+QString::number(process));
}

void MainWindow::showPing(int ping)
{
	labelPing->setText("Ping: " + QString::number(ping)+"ms");
}

void MainWindow::getWallet()
{
	bittrex->getWallet(apiKey,secretKey);
}

void MainWindow::gotWalletFirstTime(QList<JBalance> _wallet)
{
	disconnect(bittrex,&JBittrex::gotWallet,this,&MainWindow::gotWalletFirstTime);
	ui->labelTryAgain->show();
	ui->groupBoxPair->show();
	ui->groupBoxEvents->show();
	ui->groupBoxBalances->show();
	ui->groupBoxOpenedOrders->show();

	if(!wallet.isEmpty())
		wallet.clear();
	wallet = _wallet;
	if(!_wallet.isEmpty())
		_wallet.clear();
	showBalances(wallet);
	mainTimer->setInterval(2000);
	mainTimer->start();
	mainProcess();
	process = 0;
	showProcess();

}

void MainWindow::gotWallet(QList<JBalance> _wallet)
{
	if(!wallet.isEmpty())
		wallet.clear();
	wallet = _wallet;
	if(!_wallet.isEmpty())
		_wallet.clear();
	showBalances(wallet);
}

void MainWindow::gotTickers(QList<JTickers> _tickers)
{
	disconnect(bittrex,&JBittrex::gotTickers,this,&MainWindow::gotTickers);
	if(!tickers.isEmpty())
		tickers.clear();
	//tickersShow = _tickers;
	for(JTickers ticker : _tickers)
	{
		if(ticker.getMarketName()==marketName)
		{
			ui->groupBoxPair->setTitle(marketName);
			ui->labelAsk->setText(QString::number(ticker.getAsk(),'g',8));
			ui->labelBid->setText(QString::number(ticker.getBid(),'g',8));
			ui->labelSpread->setText(QString::number(ticker.getSpread(),'g',8));
			break;
		}
	}

	if(process==0)
	{
		uint time = QDateTime::currentDateTime().toTime_t();
		time-= oldMounth*2629743;
		for(JTickers ticker : _tickers)
		{
			if(ticker.getCreatedUNIX()<time)
			{
				if(ticker.getBaseCurrency() == mainCurrency)
				{
					tickers << ticker;
				}
			}
		}
		if(!_tickers.isEmpty())
			_tickers.clear();
		if(process == 0)
		{
			if(!tickers.isEmpty())
			{
				process = 1;
				showProcess();
			}

		}
	}
}

void MainWindow::showBalances(QList<JBalance> &_wallet)
{
	if(ui->checkBox->isChecked())
	{
		QList<JBalance> walletWithoutZeroBalances;
		if(!_wallet.isEmpty())
		{
			for(JBalance balance : _wallet)
			{
				if(!(balance.getAvailable()==0 && balance.getBalance()==0))
				{
					walletWithoutZeroBalances<<balance;
				}
			}
		}
		listModelBalances->setBalances(walletWithoutZeroBalances);
		if(!walletWithoutZeroBalances.isEmpty()){
			walletWithoutZeroBalances.clear();
		}
	}else{
		listModelBalances->setBalances(_wallet);
	}
	ui->tableViewBalances->setColumnWidth(0,ui->tableViewBalances->width()/3);
	ui->tableViewBalances->setColumnWidth(1,ui->tableViewBalances->width()/3);
	ui->tableViewBalances->setColumnWidth(2,ui->tableViewBalances->width()/3);
}

void MainWindow::showOrders()
{
	listModelOpenedOrder->clear();
	if(!openedSellOrders.isEmpty())
	{
		 for(int i = 0;i<openedSellOrders.count();i++)
		 {
			 listModelOpenedOrder->addRow(openedSellOrders.at(i).getOrderUuid(),openedSellOrders.at(i).getPrice(),openedSellOrders.at(i).getQuantity(),
											 openedSellOrders.at(i).getType());
		 }

	}
	if(!openedBuyOrders.isEmpty())
	{
		 for(int i = 0;i<openedBuyOrders.count();i++)
		 {
			 listModelOpenedOrder->addRow(openedBuyOrders.at(i).getOrderUuid(),openedBuyOrders.at(i).getPrice(),openedBuyOrders.at(i).getQuantity(),
											 openedBuyOrders.at(i).getType());
		 }

	}

	ui->tableViewOpenedOrders->setColumnWidth(0,ui->tableViewBalances->width()/3);
	ui->tableViewOpenedOrders->setColumnWidth(1,ui->tableViewBalances->width()/3);
	ui->tableViewOpenedOrders->setColumnWidth(2,ui->tableViewBalances->width()/3);
	ui->tableViewOpenedOrders->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);

}

void MainWindow::gotMarkets(QList<JMarket> _markets)
{
	disconnect(bittrex,&JBittrex::gotMarkets,this,&MainWindow::gotMarkets);
	if(!_markets.isEmpty())
	{
		for(JMarket market : _markets)
		{
			if(market.getMarketName() == tickerSpread.getMarketName())
			{
				minTradeSize = market.getMinTradeSize();
				marketName = market.getMarketName();
				process = 3;
				showProcess();
			}
		}
	}

}

void MainWindow::openedBuyOrder(QString _uuid)
{
	bittrex->getWallet(apiKey,secretKey);
	//openedBuyOrders << new JOrder(orderId);
	openedBuyOrders.last().setOrderUuid(_uuid);
	openedBuyOrders.last().setType("Buy");
	buyOrders.removeFirst();
	if(!buyOrders.isEmpty())
	{
		process = 4;
		showProcess();
	}else{
		mainTimer->setInterval(5000);
		process = 5;
		showProcess();
		showOrders();
		listModelEvents->addEvent(QDateTime::currentDateTime().toString("dd.MM.yyyy hh:mm:ss ")+"Ордера на покупку виставлены.");
		sendMesageToTelegram("Ордера на покупку виставлены.");
	}
}

void MainWindow::openedSellOrder(QString _uuid)
{
	bittrex->getWallet(apiKey,secretKey);
	if(process == 13)
	{
		openedSellOrders <<JOpenedOrder(_uuid);
		openedSellOrders.last().setType("Sell");
		openedSellOrders.last().setPrice(midPrice*(1+profit));
		openedSellOrders.last().setQuantity(summQuantity-0.00000001);
		process = 5;
		showProcess();
		showOrders();
		listModelEvents->addEvent(QDateTime::currentDateTime().toString("dd.MM.yyyy hh:mm:ss ")+"Ордер на продажу виставлен/переставлен.");
		listModelEvents->addEvent(QDateTime::currentDateTime().toString("dd.MM.yyyy hh:mm:ss ")+"Мониторю.");
		sendMesageToTelegram("Ордер на продажу виставлен/переставлен.");
		sendMesageToTelegram("Мониторю.");
	}
}

void MainWindow::gotOpenOrders(QList<JOpenedOrder> _openedOrders)
{
	qDebug()<<"gotOpenOrders";
	int n = 0;
	if(!openedBuyOrders.isEmpty())
	{
		for(JOpenedOrder _openedBuyOrder:openedBuyOrders)
		{
			bool buyOrderExecuted = true;
			for(JOpenedOrder _openedOrder: _openedOrders)
			{
				if(_openedBuyOrder.getOrderUuid() == _openedOrder.getOrderUuid())
				{
					buyOrderExecuted = false;
					//double n = _openedOrder.getQuantity()-_openedOrder.getQuantityRemaining()
					qDebug()<<_openedOrder.getQuantity()-_openedOrder.getQuantityRemaining()<<"/"<<_openedOrder.getQuantity();
					if(!(_openedBuyOrder.getQuantityRemaining() == _openedOrder.getQuantityRemaining()))
						qDebug()<<"Ордер исполнен на половину";
					break;
				}
			}
			if(buyOrderExecuted)
			{
				n++;
				midPrice = (midPrice*summQuantity+ openedBuyOrders.first().getPrice()*openedBuyOrders.first().getQuantity())/(summQuantity+openedBuyOrders.first().getQuantity());
				summQuantity += openedBuyOrders.first().getQuantity();
				qDebug()<<"midPrice: "<<midPrice;
				qDebug()<<"summQuntity: "<<QString::number(summQuantity,'f',8);
				openedBuyOrders.removeFirst();
				showOrders();
				process = 6;
				showProcess();
				listModelEvents->addEvent(QDateTime::currentDateTime().toString("dd.MM.yyyy hh:mm:ss ")+"Ордер на покупку исполнен.");
				sendMesageToTelegram("Ордер на покупку исполнен.");
				if(n>1)
				{
					mainTimer->stop();
					mainTimer->setInterval(60000);
					mainTimer->start();
				}else{
					if(mainTimer->interval()==60000)
					{
						mainTimer->stop();
						mainTimer->setInterval(5000);
						mainTimer->start();
					}
				}
			}
		}


//		double buyOrderExecuted = true;
//		for(JOpenedOrder _openedOrder: _openedOrders)
//		{
//			if(openedBuyOrders.first().getOrderUuid() == _openedOrder.getOrderUuid())
//			{
//				buyOrderExecuted = false;
//				qDebug()<<_openedOrder.getQuantity();
//				break;
//			}
//		}
//		if(buyOrderExecuted)
//		{
//			midPrice = (midPrice*summQuantity+ openedBuyOrders.first().getPrice()*openedBuyOrders.first().getQuantity())/(summQuantity+openedBuyOrders.first().getQuantity());
//			summQuantity += openedBuyOrders.first().getQuantity();
//			qDebug()<<"midPrice: "<<midPrice;
//			qDebug()<<"summQuntity: "<<QString::number(summQuantity,'f',8);
//			openedBuyOrders.removeFirst();
//			showOrders();
//			process = 6;
//			showProcess();
//			listModelEvents->addEvent(QDateTime::currentDateTime().toString("dd.MM.yyyy hh:mm:ss ")+"Ордер на покупку исполнен.");
//			sendMesageToTelegram("Ордер на покупку исполнен.");
//		}
	}
	if(!openedSellOrders.isEmpty())
	{
		double sellOrderExecuted = true;
		for(JOpenedOrder _openedOrder: _openedOrders)
		{
			if(openedSellOrders.first().getOrderUuid() == _openedOrder.getOrderUuid())
			{
				sellOrderExecuted = false;
				qDebug()<<_openedOrder.getQuantity();
				break;
			}
		}
		if(sellOrderExecuted)
		{
			process = 7;
			showProcess();
			listModelEvents->addEvent(QDateTime::currentDateTime().toString("dd.MM.yyyy hh:mm:ss ")+"Ордер на продажу исполнен.");
			sendMesageToTelegram("Ордер на продажу исполнен.");
		}
	}


}

void MainWindow::answerFromTelegram(QNetworkReply *reply)
{
	if(!reply->error())
	{
		//qDebug()<<reply->readAll();
	}else{
		//qDebug()<<"Answer from telegram error";
	}
	reply->deleteLater();
}

void MainWindow::canceledOrder()
{
	bittrex->getWallet(apiKey,secretKey);
	if(process == 12)
	{

		if(!openedSellOrders.isEmpty())
			openedSellOrders.clear();
		process = 6;
		showProcess();
		showOrders();
	}
	if(process == 14)
	{
		if(!openedBuyOrders.isEmpty())
			openedBuyOrders.removeFirst();
		process = 7;
		showProcess();
		showOrders();
	}
}

void MainWindow::successWalletIsFalse()
{
	disconnect(bittrex,&JBittrex::successWalletIsFalse,this,&MainWindow::successWalletIsFalse);
	ui->lineEditApiKey->clear();
	ui->lineEditSecretKey->clear();
	ui->labelTryAgain->show();
	ui->groupBoxStart->show();

}

void MainWindow::on_checkBox_clicked(bool checked)
{
	showBalances(wallet);
}

void MainWindow::on_pushButton_clicked()
{
	bittrex->getWallet(apiKey,secretKey);

}
void MainWindow::sendMesageToTelegram(QString _mesage)
{
	QUrl url;
	url.setUrl("https://api.telegram.org/bot571686449:AAGj56dmUTo1D44r5eXIkLBw4B2Eq-ORiRY/sendMessage?chat_id=324087454&text="+QDateTime::currentDateTime().toString("dd.MM.yy hh:mm:ss")+": "+_mesage);
	NAMTelegram->get(QNetworkRequest(url));
}

void MainWindow::mainProcess()
{
	switch(process)
	{
	case 0://получение котировок для нашей валюты.
		connect(bittrex,&JBittrex::gotTickers,this,&MainWindow::gotTickers);
		bittrex->getTickers();
		return;
	case 1:

		if(!tickers.isEmpty())
		{
			double baseVolume = 0;
			for(int i = tickers.count()-1;i>=0;i--)//убираю хуевые пары.
			{
				for(int n = 0; n<badPairs.count();n++)
				{
					if(tickers.at(i).getMarketName()==badPairs.at(n))
					{
						tickers.removeAt(i);
						break;
					}
				}
			}
			for(int i = tickers.count()-1;i>=0;i--)//убираю хуевые пары.
			{
				if(tickers.at(i).getBid() < 0.00002057)
				{
					tickers.removeAt(i);
				}
			}
			for(int i = tickers.count()-1;i>=0;i--)//убираю хуевые пары.
			{

				if(tickers.at(i).getPercentUp() > 0.10)
				{
					tickers.removeAt(i);
				}
			}
			for(JTickers ticker : tickers)
			{
				if(ticker.getSpread() > minSpread)
				{
					if(ticker.getSpread() < 0.05)
					{
						if(ticker.getBaseVolume()>baseVolume)
						{
							baseVolume = ticker.getBaseVolume();
							tickerSpread = ticker;
						}
					}
				}
			}
			process = 2;
			showProcess();
		}
		return;
	case 2:
		//qDebug()<<"I am here!2";
		connect(bittrex,&JBittrex::gotMarkets,this,&MainWindow::gotMarkets);
		bittrex->getMarkets();
		return;
	case 3:
		//qDebug()<<"I am here!3";
		if(!tickers.isEmpty())
		{
			JTickers selectedTicker;
			for(JTickers ticker:tickers)
			{
				if(ticker.getMarketName()==marketName)
				{
					if(mainCurrency =="BTC")
					{
						minTradeSizeMainCurrency = 0.000501;
					}

					//minTradeSizeMainCurrency = minTradeSize * ticker->getAsk() *1.05;
					qDebug()<<minTradeSizeMainCurrency;
					selectedTicker = ticker;
				}
			}
			if(!wallet.isEmpty())
			{
				for(JBalance balance:wallet)
				{
					if(balance.getCurrency()==mainCurrency)
					{

							double x = (100*selectedTicker.getBid()-100*selectedTicker.getAsk()+selectedTicker.getAsk()*(selectedTicker.getSpread()*0.8*100))/((selectedTicker.getSpread()*0.8*100)-200);
							double priceBuy;
							double priceSell;
							priceBuy = QString::number(selectedTicker.getBid()+x*0.1,'f',8).toDouble();
							priceSell = QString::number(selectedTicker.getAsk()-x*1.9,'f',8).toDouble();
							if(priceBuy==priceSell)
								priceSell = priceSell + 0.00000001;
							profit = (priceSell-priceBuy)/priceSell;



							Deposit = deposit * balance.getAvailable();
							if(minTradeSizeMainCurrency != 0)
							{
								double summ = 0;
								for(double i = 0; i<numberOrders;i++)
								{
									//summ += 1 + martingail * i;
									summ += 1 * pow(1+martingail,i);
								}
								double stepQuantity = Deposit/summ;
								qDebug()<<"Первий ордер"<<stepQuantity;

								double maxPrice = priceBuy;
								double stepPrice;
								if(numberOrders != 1)
								{
									stepPrice = (maxPrice - (maxPrice - maxPrice * perekritie))/(numberOrders -1);
								}else{
									stepPrice = 0;
								}



								buyOrders.clear();
								if(/*minTradeSizeMainCurrency < stepQuantity*/1)
								{
									for(double i = 0; i<numberOrders;i++)
									{

											  double price = maxPrice - i * stepPrice;

											  qDebug()<<"Quantity"<<i+1<<": "<<(stepQuantity * pow(1+martingail,i))/price;
											  buyOrders << JSellOrder(price,(stepQuantity * pow(martingail,i))/price,marketName);
											  //buyOrders <<JSellOrder(price,(stepQuantity + martingail * stepQuantity * i)/price,marketName);
											  qDebug()<<"Price: "<<buyOrders.last().getPrice();
									}
									qDebug()<<selectedTicker.getMarketName();
									qDebug()<<"buyOrders.count()"<<buyOrders.count();
									mainTimer->setInterval(2000);
									process = 4;
									showProcess();
									listModelEvents->addEvent(QDateTime::currentDateTime().toString("dd.MM.yyyy hh:mm:ss ")+"Начинаю выставлять ордера на покупку.");
									sendMesageToTelegram("Начинаю выставлять ордера на покупку.");
								}else{
									listModelEvents->addEvent(QDateTime::currentDateTime().toString("dd.MM.yyyy hh:mm:ss ")+"Недоствточный баланс.");
									sendMesageToTelegram("Недоствточный баланс.");
									process = 0;
									showProcess();
									mainTimer->stop();
								}
							}
					}
				}
			}

		}
		return;
	case 4:
		connect(bittrex,&JBittrex::gotTickers,this,&MainWindow::gotTickers);
		bittrex->getTickers();
		if(!buyOrders.isEmpty())
		{
			//qDebug()<<currensyPair<<buyOrders.first()->getPrice()<<buyOrders.first()->getQuantity();
			bittrex->openBuyOrder(apiKey,secretKey,marketName,buyOrders.first().getQuantity(),buyOrders.first().getPrice());
			openedBuyOrders.append(JOpenedOrder());
			openedBuyOrders.last().setPrice(buyOrders.first().getPrice());
			openedBuyOrders.last().setQuantity(buyOrders.first().getQuantity());
			process = 11;
			showProcess();
			return;
		}
	case 5://мониторинг
		connect(bittrex,&JBittrex::gotTickers,this,&MainWindow::gotTickers);
		bittrex->getTickers();
		if(!openedBuyOrders.isEmpty())
		{
			qDebug()<<"!openedBuyOrders.isEmpty()";
			if(openedBuyOrders.count() == numberOrders)
			{
				qDebug()<<"openedBuyOrders.count() == numberOrders";
				for(JTickers ticker : tickers)
				{
					if(ticker.getMarketName() == marketName)
					{
						qDebug()<<"!!!";
						if(ticker.getBid() > (openedBuyOrders.first().getPrice()*(1+perestanovka)))
						{
							if(openedBuyOrders.first().getQuantity()==openedBuyOrders.first().getQuantityRemaining())
							{
								//ui->console->append("Цена ушла. Переставляю ордера");
								sendMesageToTelegram("Цена ушла. Переставляю ордера.");
								listModelEvents->addEvent(QDateTime::currentDateTime().toString("dd.MM.yyyy hh:mm:ss ")+"Цена ушла. Переставляю ордера.");
								process = 7;
								showProcess();
							}

						}
					}
				}
			}

		}
		if(((!openedBuyOrders.isEmpty())||(!openedSellOrders.isEmpty())))
		{
			 bittrex->getOpenOrders(apiKey,secretKey);
		}
		return;
	case 6:
		connect(bittrex,&JBittrex::gotTickers,this,&MainWindow::gotTickers);
		bittrex->getTickers();
		if(openedSellOrders.isEmpty())
		{
			process = 13;
			showProcess();
//			if(midPrice > bid*(1-otstup))
//			{
				bittrex->openSellOrder(apiKey,secretKey,marketName,summQuantity/*-0.00000001*/,midPrice*(1+profit));
//			}

		}else{
			process = 12;
			showProcess();
			bittrex->cancelOrder(apiKey,secretKey,openedSellOrders.first().getOrderUuid());
		}
		return;
	case 7:
		connect(bittrex,&JBittrex::gotTickers,this,&MainWindow::gotTickers);
		bittrex->getTickers();
		showOrders();
		if(!openedBuyOrders.isEmpty())
		{
			process = 14;
			showProcess();
			bittrex->cancelOrder(apiKey,secretKey,openedBuyOrders.first().getOrderUuid());
		}else{
				//mainTimer->stop();
				bittrex->getWallet(apiKey,secretKey);
				listModelEvents->addEvent(QDateTime::currentDateTime().toString("dd.MM.yyyy hh:mm:ss ")+"Сделка завершена");
				sendMesageToTelegram("Сделка завершена");
				if(ui->checkBoxStop->isChecked())
				{
					QApplication::closeAllWindows();
				}else{
					process = 0;
					showProcess();
					if(!buyOrders.isEmpty())
					{
						buyOrders.clear();
					}
					if(!openedBuyOrders.isEmpty())
					{
						openedBuyOrders.clear();
					}
					if(!openedSellOrders.isEmpty())
					{
						openedSellOrders.clear();
					}
					midPrice = 0;
					summQuantity = 0;
				}
		}
		return;



	case 11:
		return;
	case 12:
		return;
	case 13:
		return;
	case 14:
		return;

	}
}

void MainWindow::errorOpenBuyOreder()
{
	if(process == 11)
		process = 4;
}

void MainWindow::errorOpenSellOreder()
{
	if(process == 13)
		process = 6;
}

void MainWindow::errorCancelOrder()
{
	if(process == 12)
		process = 6;
	if(process == 14)
		process = 7;
}
