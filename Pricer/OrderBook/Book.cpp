#include "Book.h"
#include "Order.h"
#include <algorithm>


Book::Book()
	: m_currentBuySize(0),
	m_currentSellSize(0)
{
}

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

void Book::reduceOrderInBuyList(const Order & order)
{
	//std::sort = N*log2(N)
	//std::lower_bound = logbase2*(N)+ O(1)
	sortOrdersByPrice('B');

	//TODO: make sure lambda function is working
	auto lower = std::lower_bound(m_buyOrders.begin(), m_buyOrders.end(), order.m_orderId,
		[](const Order& order1, std::string rhs)
	{
		return order1.m_orderId < rhs;
	});

	//if the order is 0 or less, remove it from the vector
	lower._Ptr->m_size -= order.m_size;
	if (lower._Ptr->m_size <= 0)
	{
		std::iter_swap(lower, m_buyOrders.end());
		m_buyOrders.pop_back();
	}
}

void Book::reduceOrderInSellList(const Order & order)
{
	sortOrdersByPrice('S');

	//TODO: make sure lambda function is working
	auto lower = std::lower_bound(m_sellOrders.begin(), m_sellOrders.end(), order.m_orderId,
		[](const Order& order1, std::string rhs)
	{
		return order1.m_orderId < rhs;
	});


	//if the order is 0 or less, remove it from the vector
	lower._Ptr->m_size -= order.m_size;
	if(lower._Ptr->m_size<=0)
	{
		std::iter_swap(lower, m_sellOrders.end());
		m_sellOrders.pop_back();
	}
}


void Book::sortOrdersByPrice(const char& orderSide)
{
	//TODO:sort order by Price
	if (orderSide == 'B')
	{
		//sort the buyOrders vector
		std::sort(m_buyOrders.begin(), m_buyOrders.end(),
			[](Order& order1, Order& order2)
		{
			return (order1.m_price < order2.m_price);
		});
	}
	else if (orderSide == 'S')
	{
		//sort the sellOrders vector
		std::sort(m_sellOrders.begin(), m_sellOrders.end(),
			[](Order& order1, Order& order2)
		{
			return (order1.m_price > order2.m_price);
		});
	}
}
void Book::sortOrdersById(const char& orderSide)
{
	//sort vector in ascending order by ID.
	if (orderSide == 'B')
	{
		std::sort(m_buyOrders.begin(), m_buyOrders.end(),
			[](Order& order1, Order& order2)
		{
			return (order1.m_orderId < order2.m_orderId);
		});
	}
	else if (orderSide == 'S')
	{
		std::sort(m_sellOrders.begin(), m_sellOrders.end(),
			[](Order& order1, Order& order2)
		{
			return (order1.m_orderId < order2.m_orderId);
		});
	}
}

int Book::getCurrentBuySize()
{
	return m_currentBuySize;
}
int Book::getCurrentSellSize()
{
	return m_currentSellSize;
}
