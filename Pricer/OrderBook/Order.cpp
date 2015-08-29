#include "Order.h"

Order::Order()
	: m_timestamp(0),
	m_orderType(' '),
	m_orderId(' '),
	m_orderAction(' '),
	m_price(0),
	m_size(0)
{
}

Order::~Order()
{
}
