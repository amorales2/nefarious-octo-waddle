#pragma once

#include "Book.h"
#include <memory>
struct Order;
typedef std::shared_ptr<Order> OrderPtr;

class DataManager
{
public:
	DataManager(long long targetSize);

	Order createOrder(const std::string& orderData);

	//new functions with Unique_ptr
	void addOrderToBook(OrderPtr& order);
	void applyReduceOrder(OrderPtr& order);
	void setTargetSize(long long targetSize);

	std::string getOutputData(const char& action);
	bool targetSizeReached(const char& orderType);
	bool previousTargetSizeReached(const char& orderType);

	//TODO: name this something else
	void printOutputToFile(std::string fileName);

	//TODO
	void makePriceCurrent(const char & action);
	void makeTargetSizeCurrent(const char & action);
	long long getPrice(const char& action);

	long long DataManager::getTargetSize();
	long long DataManager::getBuyPrice();
	long long DataManager::getSellPrice();
	long long DataManager::getPreviousPrice(const char& action);
	char& reduceOrderAction();

private:
	Book m_book;
	long long m_targetSize;

	//for tracking price
	long long m_previousBuyPrice;
	long long m_previousSellPrice;

	long long m_buyPrice;
	long long m_sellPrice;

	bool m_previousBuyTargetReached;
	bool m_previousSellTargetReached;


};
