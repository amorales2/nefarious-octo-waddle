#pragma once

#include <vector>
#include "Book.h"
struct Order;

class DataManager
{
public:
	DataManager(int targetSize);

	Order createOrder(const std::string& orderData);
	bool isTransactionSizeReached(const char& orderAction);
	std::string priceOfAction(const char& orderAction);

	bool targetSizeReached(const char& orderType);
	void addOrderToBook(const Order& order);

	void applyReduceOrder(const Order& order);
	int getTargetSize();
	void setTargetSize(int targetSize);

private:
	Book m_book;
	int m_targetSize;
	bool m_SellTargetReached;
	bool m_BuyTargetReached;
};
