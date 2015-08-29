#include "DataManager.h"
#include "Order.h"
#include "Book.h"
#include <iostream>
#include <sstream>

DataManager::DataManager()
{

}

Order DataManager::createOrder(const std::string& orderData)
{
	Order order;
	std::string temp;
	std::istringstream test(orderData);

	//TODO: form this into a loop
	//timestamp
	test >> temp;
	std::cout << "substring: " << temp + "\n" << std::endl;
	order.m_timestamp = temp;

	//ordertype
	test >> temp;
	std::cout << "substring: " << temp + "\n" << std::endl;
	order.m_orderType = temp;

	//orderId
	test >> temp;
	std::cout << "substring: " << temp + "\n" << std::endl;
	order.m_orderId = temp;

	//side
	test >> temp;
	std::cout << "substring: " << temp + "\n" << std::endl;
	order.m_orderId = temp;

	//price
	test >> temp;
	std::cout << "substring: " << temp + "\n" << std::endl;
	order.m_price = std::stoi(temp);

	//size
	test >> temp;
	std::cout << "substring: " << temp + "\n" << std::endl;
	order.m_size = std::stoi(temp);
	return order;
}

void DataManager::addOrderToBook(Order& order, Book& book)
{
	if (order.m_orderType == "B")
	{

	}

	if (order.m_orderType == "S")
	{

	}
}

void DataManager::removeOrderFromBook()
{

}

bool DataManager::isTransactionSizeReached(int targetSize)
{

	return false;
}

std::string DataManager::priceOfAction()
{
	return std::string();
}