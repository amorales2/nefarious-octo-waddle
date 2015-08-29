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
	return std::string();
}
