#include "DataManager.h"
#include "Order.h"
#include "Book.h"
#include <iostream>
#include <sstream>

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

std::string DataManager::priceOfAction(const char & orderAction)
{
	//TODO
	return std::string();
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

void DataManager::addOrderToBook(const Order & order)
{
	const char orderAction = order.m_orderAction;
	if (orderAction == 'B')
	{
		m_book.addBuyOrderToBook(order);
	}
	else if (orderAction == 'S')
	{
		m_book.addSellOrderToBook(order);
	}
	else
	{
		//TODO handle exception
		std::cout << "Error: invalid orderAction on order" << order.m_orderId << std::endl;
		std::cout << "DataManager::addOrderToBook()" << std::endl;
	}
}

void DataManager::applyReduceOrder(const Order& order)
{
	//sort the buy data by ID
	m_book.sortOrdersById('B');

	//search through buy data for order.m_id
	if (m_book.buyOrdersContainOrder(order))
	{
		//if found, reduce that number by order.m_size
		m_book.reduceOrderInBuyList(order);
	}
	else
	{
		//sort the sell data by ID
		m_book.sortOrdersById('S');
	}

	//search through sell data for order.m_id
	if (m_book.sellOrdersContainOrder(order))
	{
		//if found, reduce that number by order.m_size
		m_book.reduceOrderInSellList(order);
	}
	else
	{
		std::cout << "cannot reduce order. Order not found" << std::endl;
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
