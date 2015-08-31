#include "DataManager.h"
#include "Order.h"
#include "Book.h"
#include <iostream>
#include <sstream>
#include <memory>

DataManager::DataManager(int targetSize)
	: m_book(),
	m_targetSize(targetSize),
	m_BuyTargetReached(false),
	m_SellTargetReached(false)
{
}

//creates an order from the raw logfile data and returns it
Order DataManager::createOrder(const std::string& orderData)
{
	Order order;
	std::string temp;
	std::istringstream test(orderData);

	//timestamp
	test >> temp;
	std::cout << "substring: " << temp + "\n" << std::endl;
	order.m_timestamp = std::stoi(temp);

	//ordertype
	test >> temp;
	std::cout << "substring: " << temp + "\n" << std::endl;
	order.m_orderType = temp.c_str()[0];

	//orderId
	test >> temp;
	std::cout << "substring: " << temp + "\n" << std::endl;
	order.m_orderId = temp;

	//orderAction
	test >> temp;
	std::cout << "substring: " << temp + "\n" << std::endl;
	order.m_orderAction = temp.c_str()[0];

	//price
	test >> temp;
	std::cout << "substring: " << temp + "\n" << std::endl;
	order.m_price = std::stod(temp);

	//size
	test >> temp;
	std::cout << "substring: " << temp + "\n" << std::endl;
	order.m_size = std::stoi(temp);
	return order;
}

void DataManager::addOrderToBook(std::shared_ptr<Order> order)
{
	
}

void DataManager::applyReduceOrder(std::shared_ptr<Order> order)
{

}


bool DataManager::targetSizeReached(const char & orderAction)
{

	switch (orderAction)
	{
	case 'B':
		if (m_book.getCurrentBuySize() >= m_targetSize)
		{
			return true;
		}
		return false;
	case 'S':
		if (m_book.getCurrentBuySize() >= m_targetSize)
		{
			return true;
		}
		return false;
	default:
		std::cout << "Error, invalid orderType" << std::endl;
		return false;
	}
}

void DataManager::printOutputToConsole()
{
	//TODO: build string and output to console
}

void DataManager::printOutputToFile(std::string fileName)
{
	//TODO: build string and output to file

}

void DataManager::setTargetSize(int targetSize)
{
	m_targetSize = targetSize;
}
