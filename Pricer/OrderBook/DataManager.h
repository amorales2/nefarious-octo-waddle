#pragma once

#include "Order.h"
#include "Book.h"
class Order;
class Book;

class DataManager
{

public:
	DataManager();
	Order createOrder(const std::string& orderData);
	void addOrderToBook(Order& order, Book& book);
	void removeOrderFromBook();
	bool isTransactionSizeReached(int targetSize);
	std::string priceOfAction();
};