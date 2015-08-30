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


bool DataManager::isTransactionSizeReached(const char& orderAction)
{
	if(orderAction=='S')
	{
		if (m_book.getCurrentSellSize() >= m_targetSize)
			return true;
		else
			return false;
	}
	if (orderAction == 'B')
	{
		if (m_book.getCurrentBuySize() >= m_targetSize)
			return true;
		else
			return false;
	}

	std::cout << "Invalid orderAction: DataManager::isTransactionSizeReached()"<<std::endl;
	return false;
}

std::string DataManager::priceOfAction(const char & orderAction)
{

	//TODO
	return std::string();
}


bool DataManager::targetSizeReached(const char & orderType)
{
	if (orderType == 'B')
	{
		if (m_book.getCurrentBuySize() >= m_targetSize)
		{
			return true;
		}
		return false;
	}

	if (orderType == 'S')
	{
		if (m_book.getCurrentBuySize() >= m_targetSize)
		{
			return true;
		}
		return false;
	}
	else
	{
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
	//TODO

	//sort the buy data by ID
	m_book.sortOrdersById('B');
	//search through buy data for order.m_id
	


	//if found, reduce that number by order.m_size

	//else

	//sort the sell data by ID
	//search through sell data for order.m_id
	//if found, reduce that number by order.m_size
}

int DataManager::getTargetSize()
{
	return m_targetSize;
}

void DataManager::setTargetSize(int targetSize)
{
	m_targetSize = targetSize;
}
