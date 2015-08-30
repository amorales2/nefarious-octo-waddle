#pragma once

#include <vector>
#include "Book.h"
struct Order;

class DataManager
{
public:
	DataManager(int targetSize);

	Order createOrder(const std::string& orderData);
	std::string priceOfAction(const char& orderAction);

	int DataManager::getTargetSize() { return m_targetSize; }
	bool targetSizeReached(const char& orderType);
	void addOrderToBook(const Order& order);
	void applyReduceOrder(const Order& order);
	void setTargetSize(int targetSize);
	void printOutputToConsole();
	void printOutputToFile(std::string fileName);

private:
	Book m_book;
	int m_targetSize;
	bool m_SellTargetReached;
	bool m_BuyTargetReached;
};
