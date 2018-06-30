#ifndef JOPENEDORDER_H
#define JOPENEDORDER_H

#include <QString>

class JOpenedOrder
{

private:
	QString orderUuid_;
	QString exchange_;
	QString orderType_;
	double quantity_ = 0.0;
	double quantityRemaining_ = 0.0;
	double limit_ = 0.0;
	double price_ = 0.0;
	QString type_;
public:

	JOpenedOrder(QString _orderUuid){	orderUuid_ = _orderUuid;	};
	JOpenedOrder(QString _orderUuid,QString _exchange,QString _orderType,double _quantity,double _quantityRemaining,double _limit);;
	JOpenedOrder(){};

	QString getOrderUuid() const {	return orderUuid_;	};
	QString getExchange() const {	return exchange_;	};
	QString getOrderType() const {	return orderType_;	};
	double getQuantity() const {	return quantity_;	};
	double getQuantityRemaining() const {	return quantityRemaining_;	};
	double getLimit() const {	return limit_;	};
	double getPrice() const {	return price_; };
	QString getType() const {	return type_; };

	void setOrderUuid(QString _orderUuid){	orderUuid_ = _orderUuid;	};
	void setExchange(QString _exchange){	exchange_ = _exchange;	};
	void setOrderType(QString _orderType){	orderType_ = _orderType;	};
	void setQuantity(double _quantity){	quantity_ = _quantity;	};
	void setQuantityRemaining(double _quantityRemaining){	quantityRemaining_ = _quantityRemaining;	};
	void setLimit(double _limit){	limit_ = _limit;	};
	void setPrice(double _price){	price_ = _price;	};
	void setType(QString _type){	type_ = _type;	};
};

#endif // JOPENEDORDER_H
