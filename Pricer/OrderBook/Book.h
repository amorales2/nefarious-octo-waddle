#pragma once

#include <vector>
#include <map>
#include <memory>
#include <algorithm>
#include "Order.h"

typedef std::pair<std::string, long long> orderPriceById;
typedef std::map<std::string, std::shared_ptr<Order>> orderMapById;
typedef std::shared_ptr<Order> OrderPtr;

class Book
{
public:
	Book();
	void addBuyOrderToBook(const OrderPtr& order);
	void addSellOrderToBook(const OrderPtr& order);

	void reduceOrderInBuyMap(const OrderPtr& order);
	void reduceOrderInSellMap(const OrderPtr& order);

	void sortBuyVectorByPrice();
	void sortSellVectorByPrice();

	long long priceToBuyShares(long long targetSize);
	long long priceToSellShares(long long targetSize);

	//getter functions
	long long getCurrentBuySize();
	long long getCurrentSellSize();
	OrderPtr& getLastOrderAdded();
	OrderPtr& getLastReduceOrder();

	//main data structure for orders
	orderMapById m_buyOrdersById;
	orderMapById m_sellOrdersById;
	std::vector<orderPriceById> m_buyOrdersByPrice;
	std::vector<orderPriceById> m_sellOrdersByPrice;

private:
	long long m_currentBuySize;
	long long m_currentSellSize;

	OrderPtr m_lastOrderAdded;
	OrderPtr m_lastReduceOrder;

	void removeBuyOrder(const std::string& orderId);
	void removeSellOrder(const std::string& orderId);
};
