#pragma once

#include <vector>

struct Order;

class Book
{
public:
	Book();

	void addBuyOrderToBook(const Order& order);
	void addSellOrderToBook(const Order& order);

	void reduceOrderInBuyList(const Order& order);
	void reduceOrderInSellList(const Order& order);

	void sortOrdersByPrice(const char& orderSide);
	void sortOrdersById(const char& orderSide);

	int getCurrentBuySize();
	int getCurrentSellSize();

	bool buyOrdersContainOrder(const Order& order);
	bool sellOrdersContainOrder(const Order& order);

private:
	int m_currentBuySize;
	int m_currentSellSize;
	std::vector<Order> m_buyOrders;
	std::vector<Order> m_sellOrders;
};
