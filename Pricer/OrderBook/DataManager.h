#pragma once

#include "Book.h"
#include <memory>
struct Order;

class DataManager
{
public:
	DataManager(int targetSize);

	Order createOrder(const std::string& orderData);
	
	
	//new functions with Unique_ptr
	void addOrderToBook(std::shared_ptr<Order> order);
	void applyReduceOrder(std::shared_ptr<Order> order);

	//remove old
	void addOrderToBook(const Order& order);
	void applyReduceOrder(const Order& order);


	void setTargetSize(int targetSize);

	//TODO
	void printOutputToConsole();
	bool targetSizeReached(const char& orderType);
	void printOutputToFile(std::string fileName);
	int DataManager::getTargetSize() { return m_targetSize; }

private:
	Book m_book;
	int m_targetSize;
	bool m_SellTargetReached;
	bool m_BuyTargetReached;
};
