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
	void addOrderToBook(OrderPtr order);
	void applyReduceOrder(OrderPtr order);
	void setTargetSize(int targetSize);

	std::string getOutputData(const char& action);
	bool targetSizeReached(const char& orderType);
	bool previousTargetSizeReached(const char& orderType);

	//TODO: name this something else
	void printOutputToFile(std::string fileName);

	//TODO
	void makePriceCurrent(const char & action);
	void makeTargetSizeCurrent(const char & action);
	double getPrice(const char& action);

	int DataManager::getTargetSize();
	double DataManager::getBuyPrice();
	double DataManager::getSellPrice();
	double DataManager::getPreviousBuyPrice();
	double DataManager::getPreviousSellPrice();
	char& reduceOrderAction();

private:
	Book m_book;
	int m_targetSize;

	//for tracking price
	long long m_previousBuyPrice;
	long long m_previousSellPrice;

	long long m_buyPrice;
	long long m_sellPrice;

	bool m_previousBuyTargetReached;
	bool m_previousSellTargetReached;


};
