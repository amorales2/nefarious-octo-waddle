#pragma once

#include <vector>
#include "Order.h"
#include "Book.h"

struct Order;
class Book;

class DataManager
{
public:
	DataManager(int targetSize);
	int m_targetSize;
	Order createOrder(const std::string& orderData);
	bool isTransactionSizeReached(int targetSize);
	std::string priceOfAction();

	bool targetSizeReached(const char& orderType);
	void addOrderToBook(const Order& order);
	void applyReduceOrder(const Order& order);

private:
	Book m_book;
};
