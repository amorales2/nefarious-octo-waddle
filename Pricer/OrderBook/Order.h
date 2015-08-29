#pragma once

#include <string>

struct Order
{
	std::string m_timestamp;
	std::string m_orderType;
	std::string m_orderId;
	std::string m_side;
	int m_price;
	int m_size;

	Order();
	Order(std::string& timestamp, std::string& orderType,
		std::string& orderId, std::string& side, int& price, int& size);

	~Order();
};