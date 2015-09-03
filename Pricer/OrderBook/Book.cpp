#include "Book.h"
#include <algorithm>
#include <assert.h>


Book::Book()
	: m_currentBuySize(0),
	m_currentSellSize(0)
{
}

void Book::addBuyOrderToBook(OrderPtr order)
{
	//place in map
	m_buyOrdersById[order->m_orderId] = order;

	//place in vector
	m_buyOrdersByPrice.push_back(orderPriceById(order->m_orderId, order->m_price));

	//increase current size
	m_currentBuySize += order->m_size;

	//track last order
	m_lastOrderAdded = order;
}

void Book::addSellOrderToBook(OrderPtr order)
{
	//place in map
	m_sellOrdersById[order->m_orderId] = order;

	//place in vector
	m_sellOrdersByPrice.push_back(orderPriceById(order->m_orderId, order->m_price));

	//increase current size
	m_currentSellSize += order->m_size;

	//track last order
	m_lastOrderAdded = order;
}

void Book::reduceOrderInBuyMap(OrderPtr order)
{
	m_lastReduceOrder = order;
	m_lastReduceOrder->m_orderAction = m_buyOrdersById.at(order->m_orderId)->m_orderAction;


	//reduce size
	m_currentBuySize -= m_buyOrdersById[order->m_orderId]->m_size;

	//reduce the order in BUY map by looking up its ID
	m_buyOrdersById.at(order->m_orderId)->m_size -= order->m_size;

	//check that the order hasnt dropped to ZERO
	if (m_buyOrdersById.at(order->m_orderId)->m_size <= 0)
	{
		//delete order from map
		removeBuyOrder(order->m_orderId);
	}
}

void Book::reduceOrderInSellMap(OrderPtr order)
{
	m_lastReduceOrder = order;
	m_lastReduceOrder->m_orderAction = m_sellOrdersById.at(order->m_orderId)->m_orderAction;

	//reduce size
	m_currentSellSize -= m_sellOrdersById[order->m_orderId]->m_size;

	//reduce the order in SELL map by looking up its ID
	m_sellOrdersById[order->m_orderId]->m_size -= order->m_size;


	//check that the order has not dropped to ZERO
	if (m_sellOrdersById[order->m_orderId]->m_size <= 0)
	{
		removeSellOrder(order->m_orderId);
	}
}

void Book::removeBuyOrder(const std::string& orderId)
{
	auto tempID = orderId;
	auto tempPrice = m_buyOrdersById[orderId]->m_price;
	orderPriceById tempPair(tempID, tempPrice);

	auto it = std::lower_bound(m_buyOrdersByPrice.begin(), m_buyOrdersByPrice.end(), tempPair,
		[](const orderPriceById& order1, const orderPriceById& order2)
	{
		return order1.second < order2.second;
	});
	std::iter_swap(it, m_buyOrdersByPrice.end() - 1);
	m_buyOrdersByPrice.pop_back();

	//delete from map
	m_buyOrdersById.erase(orderId);
}

void Book::removeSellOrder(const std::string& orderId)
{
	//delete from vector
	auto tempID = orderId;
	auto tempPrice = m_sellOrdersById[orderId]->m_price;
	orderPriceById tempPair(tempID, tempPrice);

	auto it = std::lower_bound(m_sellOrdersByPrice.begin(), m_sellOrdersByPrice.end(), tempPair,
		[](const orderPriceById& order1, const orderPriceById& order2)
	{
		return order1.second < order2.second;
	});
	std::iter_swap(it, m_sellOrdersByPrice.end() - 1);
	m_sellOrdersByPrice.pop_back();

	//delete from map
	m_sellOrdersById.erase(orderId);
}

//TODO test
void Book::sortBuyVectorByPrice()
{

	std::sort(m_buyOrdersByPrice.begin(), m_buyOrdersByPrice.end(),
		[](const orderPriceById& lhs, const orderPriceById& rhs)
	{
		return(lhs.second < rhs.second);
	});
}

//TODO test
void Book::sortSellVectorByPrice()
{
	std::sort(m_sellOrdersByPrice.begin(), m_sellOrdersByPrice.end(),
		[](const orderPriceById& lhs, const orderPriceById& rhs)
	{
		return(lhs.second > rhs.second);
	});
}

bool Book::checkBuyMapForOrder(const OrderPtr& order)
{
	auto it = m_buyOrdersById.find(order->m_orderId);
	if (it != m_buyOrdersById.end())
	{
		return true;
	}
	else
	{
		return false;
	}
}

bool Book::checkSellMapForOrder(const OrderPtr& order)
{
	auto it = m_sellOrdersById.find(order->m_orderId);
	if (it != m_sellOrdersById.end())
	{
		return true;
	}
	else
	{
		return false;
	}
}

long long Book::priceToSellShares(int targetSize)
{
	//When BUYING shares, we want to purchase the LEAST expensive first from the SELL list

	auto totalPrice = 0;
	auto tempPrice = 0;
	auto counter = 0;
	int tempSize;
	std::string tempId;

	//sort the sell vector by price
	sortSellVectorByPrice();

	while (true)
	{
		assert(m_sellOrdersByPrice.at(counter).second);// failing here

		tempPrice = m_sellOrdersByPrice.at(counter).second;
		tempId = m_sellOrdersByPrice.at(counter).first;
		tempSize = m_sellOrdersById[tempId]->m_size;

		//if the amount of shares is less than the remaining targetSize
		if (tempSize <= targetSize)
		{
			targetSize -= tempSize;
			totalPrice += tempPrice + (tempSize*tempPrice);
		}
		else
		{
			totalPrice += (targetSize*tempPrice);
			targetSize = 0;
		}
		++counter;

		//if the target size has reached zero, we are done buying
		if (targetSize <= 0) break;
	}

	return totalPrice;
}

long long Book::priceToBuyShares(int targetSize)
{
	//When SELLING shares, we want to sell the MOST expensive first from the BUY list

	auto totalPrice = 0;
	auto tempPrice = 0;
	int counter = 0;
	int tempSize;
	std::string tempId;

	//sort the sell vector by price
	sortSellVectorByPrice();

	while (true)
	{
		assert(m_buyOrdersByPrice.at(counter).second);

		tempPrice = m_buyOrdersByPrice.at(counter).second;
		tempId = m_buyOrdersByPrice.at(counter).first;
		tempSize = m_buyOrdersById[tempId]->m_size;

		//if the amount of shares is less than the remaining targetSize
		if (tempSize <= targetSize)
		{
			targetSize -= tempSize;
			totalPrice += tempPrice + (tempSize*tempPrice);
		}
		else
		{
			totalPrice += (targetSize*tempPrice);
			targetSize = 0;
		}
		++counter;

		//if the target size has reached zero, we are done buying
		if (targetSize <= 0) break;
	}

	return totalPrice;
}

//get member data
OrderPtr Book::getLastOrderAdded()
{
	return m_lastOrderAdded;
}
OrderPtr Book::getLastReduceOrder()
{
	return m_lastReduceOrder;
}
int Book::getCurrentBuySize()
{
	return m_currentBuySize;
}
int Book::getCurrentSellSize()
{
	return m_currentSellSize;
}
