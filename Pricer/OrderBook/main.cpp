#include <iostream>
#include <fstream>
#include <string>
#include <memory>
#include "DataManager.h"


static void outputToFile(std::ofstream outputFile, const std::string& text)
{

	outputFile.close();
}




int main(int argc, char *argv[])
{
	std::ofstream outputFile;
	outputFile.open("test.out");

	//TODO: fix hard coded value
	std::ifstream file("pricer1.in");
	std::string line;
	long long targetSize = std::stoi(argv[2]);
	DataManager dataManager(targetSize);

	if (file.is_open())
		while (getline(file, line))
		{
			auto tempOrder = std::make_shared<Order>(dataManager.createOrder(line));

			if (tempOrder->m_orderType == 'A')//add order
			{
				//add order to the book
				dataManager.addOrderToBook(tempOrder);
				
				const char& tempOrderAction = tempOrder->m_orderAction;

				//check if the targetSize had been reached
				if (dataManager.targetSizeReached(tempOrderAction))
				{
					//get the price
					auto tempPrice = dataManager.getPrice(tempOrderAction);

					//if the data is not the same as the previous output, then we can print
					if (tempPrice != dataManager.getPreviousPrice(tempOrderAction))
					{
						//output data
						std::cout << dataManager.getOutputData(tempOrderAction);
						//outputFile << dataManager.getOutputData(tempOrderAction);
						//set current price to previous price
						dataManager.makePriceCurrent(tempOrderAction);
						dataManager.makeTargetSizeCurrent(tempOrderAction);			
					}
				}

				//targetSize is no longer reached
				else if (dataManager.previousTargetSizeReached(tempOrderAction))
				{
					//output data
					std::cout << tempOrder->m_timestamp << " " + tempOrderAction << " N/A" << std::endl;
					//outputFile << (tempOrder->m_timestamp + " " + std::to_string(tempOrderAction) + " N/A")<< std::endl;
					//set current price to previous price
					dataManager.makePriceCurrent(tempOrderAction);
					dataManager.makeTargetSizeCurrent(tempOrderAction);		
				}
			}
			else if (tempOrder->m_orderType == 'R')//reduce order
			{
				dataManager.applyReduceOrder(tempOrder);
				const char& tempOrderAction = dataManager.reduceOrderAction();

				//check if the targetSize had been reached previously
				if (dataManager.targetSizeReached(tempOrderAction))
				{

					//get the price
					auto tempPrice = dataManager.getPrice(tempOrderAction);

					//if the data is not the same as the previous output, then we can print
					if (tempPrice != dataManager.getPreviousPrice(tempOrderAction))
					{
						//output data
						std::cout << dataManager.getOutputData(tempOrderAction);
						//outputFile << dataManager.getOutputData(tempOrderAction);
						//set current price to previous price
						dataManager.makePriceCurrent(tempOrderAction);
						dataManager.makeTargetSizeCurrent(tempOrderAction);
					}
				}
				//targetSize is no longer reached
				else if (dataManager.previousTargetSizeReached(tempOrderAction))
				{
					//output data
					std::cout << tempOrder->m_timestamp << " " << ((tempOrderAction=='B') ? "S" : "B") << " N/A" << std::endl;
					//outputFile << std::to_string(tempOrder->m_timestamp) + " " + ((tempOrderAction == 'B') ? "S" : "B") + " N/A" << std::endl;
					
					//set current price to previous price
					dataManager.makePriceCurrent(tempOrderAction);
					dataManager.makeTargetSizeCurrent(tempOrderAction);
				}
			}
		}
	//std::cout << "complete";
	file.close();
	std::cin.get();
	return 0;
}
