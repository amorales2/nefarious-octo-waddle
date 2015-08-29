#pragma once

#include <vector>
struct Order;

class Book
{
public:
	Book();

	void addBuyOrderToBook(const Order& order);
	void addSellOrderToBook(const Order& order);
	
	void applyReduceOrder(const Order& order);

	void sortOrdersByPrice(std::string orderSide);
	void sortOrdersById(std::string orderSide);

	int getCurrentBuySize();
	int getCurrentSellSize();

private:
	int m_currentBuySize;
	int m_currentSellSize;
	std::vector<Order> m_buyOrders;
	std::vector<Order> m_sellOrders;
	void removeOrderFromBook(const Order& order);
};
