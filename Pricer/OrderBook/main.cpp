#include <iostream>
#include <fstream>
#include <string>
#include <memory>
#include "DataManager.h"

int main(int argc, char *argv[])
{
	std::ofstream outputFile;
	outputFile.open("test.out");

	//TODO: fix hard coded value
	std::ifstream file("pricer.in");
	std::ofstream outFile;
	outFile.open("test.out", std::ofstream::binary);
	std::string line;
	int targetSize = 10000;//std::stoi(argv[2]);
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
					//if the data is not the same as the previous output, then we can print
					if (dataManager.updatePrice(tempOrderAction))
					{
						//output data
						//std::cout << 
						auto output = dataManager.getOutputData(tempOrder);
						outFile.write(output.c_str(),output.length());
						dataManager.updateTargetSizeReached(tempOrderAction);
					}
				}

				//targetSize is no longer reached
				else if (dataManager.previousTargetSizeReached(tempOrderAction))
				{
					//output data
					//std::cout << tempOrder->m_timestamp << " " + tempOrderAction << " N/A" << std::endl;
					auto output((std::to_string(tempOrder->m_timestamp)+" ") + (tempOrderAction +" NA\n"));
					outFile.write(output.c_str(), output.length());
					dataManager.updateTargetSizeReached(tempOrderAction);
					dataManager.updatePrice(tempOrderAction);
				}
			}
			else if (tempOrder->m_orderType == 'R')//reduce order
			{
				dataManager.applyReduceOrder(tempOrder);
				const char& tempOrderAction = dataManager.reduceOrderAction();

				//check if the targetSize had been reached previously
				if (dataManager.targetSizeReached(tempOrderAction))
				{
					//if the data is not the same as the previous output, then we can print
					if (dataManager.updatePrice(tempOrderAction))
					{
						//output data
						//std::cout << dataManager.getOutputData(tempOrder);
						auto output = dataManager.getOutputData(tempOrder);
						outFile.write(output.c_str(), output.length());
						//set current price to previous price
						dataManager.updateTargetSizeReached(tempOrderAction);
					}
				}
				//targetSize is no longer reached
				else if (dataManager.previousTargetSizeReached(tempOrderAction))
				{
					//output data
					//std::cout << tempOrder->m_timestamp << " " << ((tempOrderAction=='B') ? "S" : "B") << " N/A" << std::endl;					
					auto output((std::to_string(tempOrder->m_timestamp) + " ") + ((tempOrderAction=='B')?"S NA\n": "B NA\n"));
					outFile.write(output.c_str(), output.length());
					//set current price to previous price
					dataManager.updateTargetSizeReached(tempOrderAction);
					dataManager.updatePrice(tempOrderAction);
				}
			}
		}
	std::cout << "complete";
	file.close();
	std::cin.get();
	return 0;
}
