#include "DataManager.h"
#include "Order.h"
#include "Book.h"
#include <iostream>
#include <sstream>
#include <memory>
#include <algorithm>

DataManager::DataManager(int targetSize)
	: m_book(),
	m_targetSize(targetSize),
	m_buyPrice(0),
	m_sellPrice(0),
	m_previousBuyTargetReached(false),
	m_previousSellTargetReached(false),
	m_previousBuyPrice(0),
	m_previousSellPrice(0)
{
}

//creates an order from the raw logfile data and returns it
Order DataManager::createOrder(const std::string& orderData)
{
	Order order;
	auto orderPtr = std::make_shared<Order>(order);

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
	//price data is stored in a long long. With a fixed decimal, it 
	//can easily be added back later. This avoids any issues that come
	//up with floating point types such as double or float.
	temp.erase(std::remove(temp.begin(), temp.end(), '.'), temp.end());
	order.m_price = std::stoll(temp);

	//size
	test >> temp;
	order.m_size = std::stoi(temp);

	return order;
}

void DataManager::addOrderToBook(OrderPtr& order)
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

void DataManager::applyReduceOrder(OrderPtr& order)
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
		return m_book.getCurrentBuySize() >= m_targetSize;
	case 'S':
		return m_book.getCurrentSellSize() >= m_targetSize;
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
		return m_previousBuyTargetReached;
	case'S':
		return m_previousSellTargetReached;
	default:
		std::cout << "Error DataManager::previousTargetSizeReached, invalid orderType" << std::endl;
		return false;
	}
}

std::string DataManager::getOutputData(const OrderPtr& order)
{
	const char orderAction = order->m_orderAction;
	const char orderType = order->m_orderType;

	//get the timestamp from the last Add order or last Reduce order
	auto tempTimestamp = std::to_string((orderType == 'A') ?
		m_book.getLastOrderAdded()->m_timestamp : m_book.getLastReduceOrder()->m_timestamp);


	if (orderAction == 'B')
	{
		auto tempPrice = std::to_string(getPrice(orderAction));

		//add the decimal back in
		tempPrice = tempPrice.substr(0, tempPrice.length() - 2) + "." + tempPrice.substr(tempPrice.length() - 2, tempPrice.length());
		return (tempTimestamp + " S " + tempPrice + "\n");
	}
	else if (orderAction == 'S')
	{
		auto tempPrice = std::to_string(getPrice(orderAction));

		//add the decimal back in
		tempPrice = tempPrice.substr(0, tempPrice.length() - 2) + "." + tempPrice.substr(tempPrice.length() - 2, tempPrice.length());
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

bool DataManager::updateTargetSizeReached(const char & action)
{
	switch (action)
	{
	case 'B':
	{
		bool newTargetSizeReached = targetSizeReached(action);
		if (m_previousBuyTargetReached != newTargetSizeReached)
		{
			m_previousBuyTargetReached = newTargetSizeReached;
			return true;
		}
		return false;
	}
	case 'S':
	{
		bool newTargetSizeReached = targetSizeReached(action);
		if (m_previousSellTargetReached != newTargetSizeReached)
		{
			m_previousSellTargetReached = newTargetSizeReached;
			return true;
		}
		return false;
	}
	default:
		std::cout << "Error in DataManager::makeTargetsizeCurrent,  invalid action" << std::endl;
		return false;
	}
}

bool DataManager::updatePrice(const char& action)
{
	switch (action)
	{
	case 'S':
	{
		long long newPrice = m_book.priceToSellShares(m_targetSize);
		if (m_previousSellPrice != newPrice)
		{
			m_previousSellPrice = newPrice;
			return true;
		}
		return false;
	}
	case 'B':
	{
		long long newPrice = m_book.priceToBuyShares(m_targetSize);
		if (m_previousBuyPrice != newPrice)
		{
			m_previousBuyPrice = newPrice;
			return true;
		}
		return false;
	}
	default:
		std::cout << "Error in DataManager::getPrice(), invalid action" << std::endl;
		return false;
	}
}

void DataManager::setTargetSize(long long targetSize)
{
	m_targetSize = targetSize;
}

char& DataManager::reduceOrderAction()
{
	return m_book.getLastReduceOrder()->m_orderAction;
}

long long DataManager::getPrice(const char & action)
{
	switch (action)
	{
	case 'B':
		return m_buyPrice = m_book.priceToBuyShares(m_targetSize);
	case 'S':
		return m_sellPrice = m_book.priceToSellShares(m_targetSize);
	default:
		std::cout << "Error in DataManager::getPrice, invalid order action" << std::endl;
	}
	return 0;
}
