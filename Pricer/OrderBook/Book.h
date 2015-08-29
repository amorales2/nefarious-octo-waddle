#pragma once

#include <vector>
class Order;

class Book
{
public:
	Book();
	void addBuyOrderToBook(const Order& order);
	void addSellOrderToBook(const Order& order);
	void removeOrderFromBook(const Order& order);
	void sortOrdersByPrice(std::string orderSide);
	void sortOrdersById(std::string orderSide);

private:
	int m_currentBuySize;
	int m_currentSellSize;
	std::vector<Order> m_buyOrders;
	std::vector<Order> m_sellOrders;
};
