#include "Order.h"

Order::Order()
	: m_timestamp(""),
	m_orderType(""),
	m_orderId(""),
	m_side(""),
	m_price(0),
	m_size(0)
{
}
Order::Order(std::string& timestamp, std::string& orderType,
	std::string& orderId, std::string& side, int& price, int& size)
	: m_timestamp(timestamp),
	m_orderType(orderType),
	m_orderId(orderId),
	m_side(side),
	m_size(size)
{
}

Order::~Order()
{
}