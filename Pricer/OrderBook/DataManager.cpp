#include "DataManager.h"
#include "Order.h"
#include "Book.h"
#include <iostream>
#include <sstream>

DataManager::DataManager(int targetSize)
	: m_book(),
	m_targetSize(targetSize)
{

}

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

bool DataManager::isTransactionSizeReached(int targetSize)
{

	return false;
}

std::string DataManager::priceOfAction()
{
	//TODO
	return std::string();
}


bool DataManager::targetSizeReached(const char & orderType)
{
	if (orderType == 'B')
	{
		if(m_book.getCurrentBuySize() >= m_targetSize)
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
	}
}

void DataManager::applyReduceOrder(const Order & order)
{

	//TODO
}
