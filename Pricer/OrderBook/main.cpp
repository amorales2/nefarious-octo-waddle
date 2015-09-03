#include <iostream>
#include <fstream>
#include <string>
#include <memory>
#include "DataManager.h"

int main(int argc, char *argv[])
{
	//TODO: fix hard coded value
	std::ifstream file("pricer1.in");
	auto targetSize = std::stoi(argv[2]);
	std::string line;
	DataManager dataManager(targetSize);

	if(file.is_open())
	while(getline(file,line))
	{
		auto tempOrder = std::make_shared<Order>(dataManager.createOrder(line));
		if (tempOrder->m_orderType == 'A')//add order
		{
			//add order to the book
			dataManager.addOrderToBook(tempOrder);
			char& tempOrderAction = tempOrder->m_orderAction;
			
			//check if the targetSize had been reached
			if(dataManager.targetSizeReached(tempOrderAction))
			{
				double tempPrice;
				switch(tempOrderAction)
				{
				case 'S':
					//get the SELL price
					tempPrice = dataManager.getSellPrice();

					//if the data is not the same as the previous output, then we can print
					if (tempPrice != dataManager.getPreviousSellPrice())
					{
						std::cout << dataManager.getOutputData(tempOrderAction);
						//set current price to previous price
						dataManager.makePriceCurrent(tempOrderAction);
						dataManager.makeTargetSizeCurrent(tempOrderAction);
					}
					break;
				case 'B':
					//get the BUY price
					tempPrice = dataManager.getBuyPrice();

					//if the data is not the same as the previous output, then we can print
					if (tempPrice != dataManager.getPreviousBuyPrice())
					{
						std::cout << dataManager.getOutputData(tempOrderAction);
						//set current price to previous price
						dataManager.makePriceCurrent(tempOrderAction);
						dataManager.makeTargetSizeCurrent(tempOrderAction);
					}
					break;
				default:
					std::cout << "Error, Invalid tempOrderAction in main"<<std::endl;
				}
			}	
		}
		else if (tempOrder->m_orderType == 'R')//reduce order
		{
			dataManager.applyReduceOrder(tempOrder);
			char& tempOrderAction = dataManager.reduceOrderAction();

			//check if the targetSize had been reached previously
			if (dataManager.previousTargetSizeReached(tempOrder->m_orderAction))
			{
				double tempPrice;
				switch (tempOrderAction)
				{
				case 'B':

					//if it was previously reached and is no longer, print n/a for price
					if (dataManager.targetSizeReached('B') == false)
					{
						std::cout << tempOrder->m_timestamp << " S " << " N/A" << std::endl;
						dataManager.makePriceCurrent(tempOrderAction);
						dataManager.makeTargetSizeCurrent(tempOrderAction);
						break;
					}						
					tempPrice = dataManager.getBuyPrice();

					//if the data is not the same as the previous output, then we can print
					if (tempPrice != dataManager.getPreviousSellPrice())
					{
						std::cout << dataManager.getOutputData(tempOrderAction);
						//set current price to previous price
						dataManager.makePriceCurrent(tempOrderAction);
						dataManager.makeTargetSizeCurrent(tempOrderAction);
					}
					break;
				case 'S':
					//if it was previously reached and is no longer, print n/a for price
					if (dataManager.targetSizeReached('S') == false)
					{
						std::cout << tempOrder->m_timestamp << " B " << " N/A" << std::endl;
						dataManager.makePriceCurrent(tempOrderAction);
						dataManager.makeTargetSizeCurrent(tempOrderAction);
						break;
					}

					//get the BUY price
					tempPrice = dataManager.getSellPrice();

					//if the data is not the same as the previous output, then we can print
					if (tempPrice != dataManager.getPreviousBuyPrice())
					{
						std::cout << dataManager.getOutputData(tempOrderAction);
						//set current price to previous price
						dataManager.makePriceCurrent(tempOrderAction);
						dataManager.makeTargetSizeCurrent(tempOrderAction);
					}
					break;
				default:
					std::cout << "Error, Invalid tempOrderAction in main" << std::endl;
				}
			}
		}
		
		//std::cout << line << std::endl;
	}
	
	file.close();
	std::cin.get();
	return 0;
}
