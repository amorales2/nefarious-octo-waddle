#include "Book.h"
#include "Order.h"
#include <algorithm>
#include <assert.h>


Book::Book()
	: m_currentBuySize(0),
	m_currentSellSize(0)
{
}


void Book::addBuyOrderToBook(std::shared_ptr<Order> order)
{
	//place in map
	m_buyOrdersById[order->m_orderId] = order;

	//place in vector
	m_buyOrdersByPrice.push_back(orderPriceById(order->m_orderId, order->m_price));
}

void Book::addSellOrderToBook(std::shared_ptr<Order> order)
{
	//place in map
	m_buyOrdersById[order->m_orderId] = order;

	//place in vector
	m_sellOrdersByPrice.push_back(orderPriceById(order->m_orderId, order->m_price));
}

void Book::reduceOrderInBuyList(std::shared_ptr<Order> order)
{
	//reduce the order in BUY map by looking up its ID
	m_buyOrdersById.at(order->m_orderId)->m_size -= order->m_size;

	//check that the order hasnt dropped to ZERO
	if (m_buyOrdersById.at(order->m_orderId)->m_size <= 0)
	{
		//delete order from map
		removeOrderFromBuyList(order->m_orderId);
	}
}

void Book::reduceOrderInSellList(std::shared_ptr<Order> order)
{
	//reduce the order in SELL map by looking up its ID
	m_sellOrdersById[order->m_orderId]->m_size -= order->m_size;

	//check that the order has not dropped to ZERO
	if (m_sellOrdersById[order->m_orderId]->m_size <= 0)
	{
		removeOrderFromSellList(order->m_orderId);
	}
}

//deletes from map only
void Book::removeOrderFromBuyList(std::string& orderId)
{
	//delete from map
	m_buyOrdersById.erase(orderId);
}

//deletes from map only
void Book::removeOrderFromSellList(std::string& orderId)
{	//delete from map
	m_sellOrdersById.erase(orderId);
}

//TODO test
void Book::sortBuyVectorByPrice()
{
	
	std::sort(m_buyOrdersByPrice.begin(), m_buyOrdersByPrice.end(),
		[](orderPriceById lhs, orderPriceById rhs)
	{
		return(lhs.second < rhs.second);
	});
}
//TODO test
void Book::sortSellVectorByPrice()
{
	std::sort(m_sellOrdersByPrice.begin(), m_sellOrdersByPrice.end(),
		[](orderPriceById lhs, orderPriceById rhs)
	{
		return(lhs.second > rhs.second);
	});
}

double Book::priceToBuyShares(int targetSize)
{
	//by design, do not enter this function unless the target size has been reached
	assert(targetSize >= m_currentSellSize);
	
	double price = 0.0;
	
	//sort the sell vector by price
	sortSellVectorByPrice();

	return price;
}

double Book::priceToSellShares(int targetSize)
{
	//by design, do not enter this function unless the target size has been reached
	assert(targetSize >= m_currentSellSize);

	double price = 0.0;


	return price;
}



//get member data
int Book::getCurrentBuySize()
{
	return m_currentBuySize;
}
int Book::getCurrentSellSize()
{
	return m_currentSellSize;
}
