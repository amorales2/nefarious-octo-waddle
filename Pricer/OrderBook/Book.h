#pragma once

#include <vector>
#include <map>
#include <memory>
#include <algorithm>
#include "Order.h"

typedef std::pair<std::string, long long> orderPriceById;
typedef std::shared_ptr<Order> OrderPtr;

class Book
{
public:
	Book();
	void addBuyOrderToBook(OrderPtr order);
	void addSellOrderToBook(OrderPtr order);

	void reduceOrderInBuyMap(OrderPtr order);
	void reduceOrderInSellMap(OrderPtr order);

	void sortBuyVectorByPrice();
	void sortSellVectorByPrice();

	long long priceToBuyShares(int targetSize);
	long long priceToSellShares(int targetSize);

	bool Book::checkBuyMapForOrder(const OrderPtr& order);
	bool Book::checkSellMapForOrder(const OrderPtr& order);

	//getter functions
	int getCurrentBuySize();
	int getCurrentSellSize();
	OrderPtr getLastOrderAdded();
	OrderPtr getLastReduceOrder();

private:
	int m_currentBuySize;
	int m_currentSellSize;

	OrderPtr m_lastOrderAdded;
	OrderPtr m_lastReduceOrder;

	//main data structure for orders
	std::map<std::string, std::shared_ptr<Order>> m_buyOrdersById;
	std::map<std::string, std::shared_ptr<Order>> m_sellOrdersById;
	std::vector<orderPriceById> m_buyOrdersByPrice;
	std::vector<orderPriceById> m_sellOrdersByPrice;

	void removeBuyOrder(const std::string& orderId);
	void removeSellOrder(const std::string& orderId);

};
