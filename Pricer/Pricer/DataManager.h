#pragma once

#include "Book.h"
#include <memory>

struct Order;
typedef std::shared_ptr<Order> OrderPtr;

class DataManager
{
public:
	DataManager(int targetSize);

	Order createOrder(const std::string& orderData);

	//new functions with Unique_ptr
	void addOrderToBook(OrderPtr& order);
	void applyReduceOrder(OrderPtr& order);
	void setTargetSize(long long targetSize);

	std::string getOutputData(const OrderPtr& action);
	bool targetSizeReached(const char& orderType);
	bool previousTargetSizeReached(const char& orderType);

	//TODO
	bool updateTargetSizeReached(const char & action);
	bool updatePrice(const char& action);

	int getTargetSize();
	char& reduceOrderAction();

private:
	Book m_book;
	int m_targetSize;

	long long getPrice(const char& action);


	//for tracking price
	long long m_previousBuyPrice;
	long long m_previousSellPrice;

	long long m_buyPrice;
	long long m_sellPrice;

	bool m_previousBuyTargetReached;
	bool m_previousSellTargetReached;


};
