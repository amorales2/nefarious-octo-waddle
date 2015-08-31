#pragma once

#include <vector>
#include <map>
#include <memory>

struct Order;

class Book
{
public:
	Book();
	//new functions taking in unique_ptr<Order>
	void addBuyOrderToBook(std::shared_ptr<Order> order);
	void addSellOrderToBook(std::shared_ptr<Order> order);

	void reduceOrderInBuyList(std::shared_ptr<Order> order);
	void reduceOrderInSellList(std::shared_ptr<Order> order);

	void removeOrderFromBuyList(std::string& orderId);
	void removeOrderFromSellList(std::string& orderId);

	void sortBuyVectorByPrice();
	void sortSellVectorByPrice();

	double priceToBuyShares(int targetSize);
	double priceToSellShares(int targetSize);
	
	//getter functions
	int getCurrentBuySize();
	int getCurrentSellSize();

private:
	int m_currentBuySize;
	int m_currentSellSize;

	//main data structure for orders
	//orderPriceById.first = ID, orderPriceById.second = price
	typedef std::pair<std::string, double> orderPriceById;
	std::map<std::string, std::shared_ptr<Order>> m_buyOrdersById;
	std::map<std::string, std::shared_ptr<Order>> m_sellOrdersById;
	std::vector<orderPriceById> m_buyOrdersByPrice;
	std::vector<orderPriceById> m_sellOrdersByPrice;


	//TODO: remove old
	std::vector<Order> m_buyOrders;
	std::vector<Order> m_sellOrders;
};
