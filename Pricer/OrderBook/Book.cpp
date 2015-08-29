#include "Book.h"
#include "Order.h"
#include <algorithm>

void Book::addBuyOrderToBook(const Order& order)
{
	//add the buy order to the vector
	m_buyOrders.push_back(order);

	//increase the total buy orders
	m_currentBuySize += order.m_size;
}

void Book::addSellOrderToBook(const Order& order)
{
	//add the sell order to the vector
	m_sellOrders.push_back(order);

	//increase the total cell orders
	m_currentSellSize += order.m_size;
}

void Book::removeOrderFromBook(const Order& order)
{
	//TODO: SEARCH THROUGH DATASTRUCTURE AND REMOVE THE ORDER BY THE CORRECT AMOUNT
}

void Book::sortOrdersByPrice(std::string orderSide)
{
	//TODO:sort order by Price
	if (orderSide == "B")
	{
		//sort the buyOrders vector
		std::sort(m_buyOrders.begin(), m_buyOrders.end(),
			[](Order& order1, Order& order2)
		{
			return (order1.m_price < order2.m_price);
		});
	}
	else if (orderSide == "S")
	{
		//sort the sellOrders vector
		std::sort(m_sellOrders.begin(), m_sellOrders.end(),
			[](Order& order1, Order& order2)
		{
			return (order1.m_price > order2.m_price);
		});
	}
}
void Book::sortOrdersById(std::string orderSide)
{
	//TODO:sort order by Id
	if (orderSide == "B")
	{
		std::sort(m_buyOrders.begin(), m_buyOrders.end(),
			[](Order& order1, Order& order2) { return (order1.m_orderId < order2.m_orderId); });
	}
	else if (orderSide == "S")
	{

	}
}
Book::Book()
	: m_currentBuySize(0),
	m_currentSellSize(0)
{

}
