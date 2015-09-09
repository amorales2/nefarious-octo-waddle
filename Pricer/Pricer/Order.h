#pragma once
#include <string>

struct Order
{
	int m_timestamp;
	char m_orderType;//Add or Reduce
	std::string m_orderId;//unique identifier for an order
	char m_orderAction;//previously m_side. Buy or Sell
	long long m_price;
	unsigned int m_size;
	
	Order();
	~Order();
};
