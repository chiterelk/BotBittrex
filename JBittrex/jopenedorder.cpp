#include "jopenedorder.h"


JOpenedOrder::JOpenedOrder(QString _orderUuid, QString _exchange, QString _orderType, double _quantity, double _quantityRemaining, double _limit)
{
	orderUuid_ = _orderUuid;
	exchange_ = _exchange;
	orderType_ = _orderType;
	quantity_ = _quantity;
	quantityRemaining_ = _quantityRemaining;
	limit_ = _limit;
}
