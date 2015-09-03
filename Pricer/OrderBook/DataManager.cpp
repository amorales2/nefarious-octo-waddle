#include "DataManager.h"
#include "Order.h"
#include "Book.h"
#include <iostream>
#include <sstream>
#include <memory>


DataManager::DataManager(int targetSize)
	: m_book(),
	m_targetSize(targetSize),
	m_buyPrice(0.0),
	m_sellPrice(0.0),
	m_previousBuyTargetReached(false),
	m_previousSellTargetReached(false)

{
}

//creates an order from the raw logfile data and returns it
Order DataManager::createOrder(const std::string& orderData)
{
	Order order;
	//auto orderPtr = std::make_shared<Order>(order);

	std::string temp;
	std::istringstream test(orderData);

	//timestamp
	test >> temp;
	order.m_timestamp = std::stoi(temp);

	//ordertype
	test >> temp;
	order.m_orderType = temp.c_str()[0];

	//orderId
	test >> temp;
	order.m_orderId = temp;

	//orderAction
	test >> temp;
	order.m_orderAction = temp.c_str()[0];

	//price
	test >> temp;

	//remove the decimal from the string
	temp.erase(std::remove(temp.begin(), temp.end(), '.'), temp.end());
	order.m_price = std::stoi(temp);


	//size
	test >> temp;
	order.m_size = std::stoi(temp);


	return order;
}

void DataManager::addOrderToBook(OrderPtr order)
{
	if (order->m_orderAction == 'B')
	{
		m_book.addBuyOrderToBook(order);
	}
	else if (order->m_orderAction == 'S')
	{
		m_book.addSellOrderToBook(order);
	}
}

void DataManager::applyReduceOrder(OrderPtr order)
{

	//search for order in buyMap first
	auto it = m_book.m_buyOrdersById.find(order->m_orderId);
	if (it != m_book.m_buyOrdersById.end())
	{
		m_book.reduceOrderInBuyMap(order);
		return;
	}

	//search for order in sellMap
	it = m_book.m_sellOrdersById.find(order->m_orderId);
	if (it != m_book.m_sellOrdersById.end())
	{
		m_book.reduceOrderInSellMap(order);
		return;
	}

	std::cout << "Error: reduce order id " << order->m_orderId << " can't be found" << std::endl;

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
		if (m_book.getCurrentSellSize() >= m_targetSize)
		{
			return true;
		}
		return false;
	default:
		std::cout << "Error, invalid orderType" << std::endl;
		return false;
	}
}

bool DataManager::previousTargetSizeReached(const char & orderType)
{
	switch (orderType)
	{
	case 'B':
		if (m_previousBuyTargetReached)
			return true;
		return false;
	case'S':
		if (m_previousSellTargetReached)
			return true;
		return false;
	default:
		std::cout << "Error DataManager::previousTargetSizeReached, invalid orderType" << std::endl;
	}
	return false;
}

std::string DataManager::getOutputData(const char& action)
{
	//TODO: build string and output to console

	if (action == 'B')
	{
		auto tempTimestamp = std::to_string(m_book.getLastOrderAdded()->m_timestamp);
		auto tempPrice = std::to_string(getBuyPrice());
		return (tempTimestamp + " S " + tempPrice + "\n");
	}
	else if (action == 'S')
	{
		auto tempTimestamp = std::to_string(m_book.getLastOrderAdded()->m_timestamp);
		auto tempPrice = std::to_string(getSellPrice());
		return (tempTimestamp + " B " + tempPrice + "\n");
	}
	else
	{
		std::cout << "Error DataManager::getOutputData, invalid action" << std::endl;
		return "";
	}
}

int DataManager::getTargetSize()
{
	return m_targetSize;
}

long long DataManager::getBuyPrice()
{
	if (m_buyPrice == 0)
	{
		m_buyPrice = m_book.priceToBuyShares(m_targetSize);
		return m_buyPrice;
	}
	return m_buyPrice;
}

long long DataManager::getSellPrice()
{
	if (m_sellPrice == 0)
	{
		m_sellPrice = m_book.priceToSellShares(m_targetSize);
		return m_sellPrice;
	}
	return m_sellPrice;
}

void DataManager::printOutputToFile(std::string fileName)
{
	//TODO: build string and output to file
}

void DataManager::makePriceCurrent(const char & action)
{
	switch (action)
	{
	case 'B':
		m_previousBuyPrice = m_buyPrice;
		m_buyPrice = 0;
		break;
	case 'S':
		m_previousSellPrice = m_sellPrice;
		m_sellPrice = 0;
		break;
	default:
		std::cout << "Error in DataManager::makePriceCurrent,  invalid action" << std::endl;
		break;
	}
}

void DataManager::makeTargetSizeCurrent(const char & action)
{
	switch (action)
	{
	case 'B':
		m_previousBuyTargetReached = targetSizeReached(action);
		break;
	case 'S':
		m_previousSellTargetReached = targetSizeReached(action);
		break;
	default:
		std::cout << "Error in DataManager::makeTargetsizeCurrent,  invalid action" << std::endl;
		break;
	}
}

long long DataManager::getPrice(const char & action)
{
	switch (action)
	{
	case 'B':
		return getSellPrice();
	case 'S':
		return getBuyPrice();
	default:
		std::cout << "Error in DataManager::getPrice(), invalid action" << std::endl;
		return 0;
	}
}

void DataManager::setTargetSize(int targetSize)
{
	m_targetSize = targetSize;
}
long long DataManager::getPreviousBuyPrice()
{
	return m_previousBuyPrice;
}
long long DataManager::getPreviousSellPrice()
{
	return m_previousSellPrice;
}
char& DataManager::reduceOrderAction()
{
	return m_book.getLastReduceOrder()->m_orderAction;
}
