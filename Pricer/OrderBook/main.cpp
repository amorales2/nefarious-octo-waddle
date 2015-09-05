#include <iostream>
#include <fstream>
#include <string>
#include <memory>
#include "DataManager.h"

int main(int argc, char *argv[])
{
	//check for the correct arguments. Provide feedback for incorrect arguments
	if (argc < 2)
	{
		std::cout << "Missing target-size argument" << std::endl;
		return -1;
	}
	else if (argc>2)
	{
		std::cout << "Invalid command line arguments" << std::endl;
		return -1;
	}

	//set targetsize from command line argument. 
	int targetSize = std::stoi(argv[argc - 1]);

	//output file named according to the targetsize
	std::ofstream outputFile;
	std::string outFileName = "pricer." + std::to_string(targetSize) + ".out";
	outputFile.open(outFileName);

	//line is the temp value from string buffer, or file
	std::string line;
	std::vector<std::string> inputVector;

	//bool to determine if we are reading from a file or buffered input
	bool readFromFile;

	//logfile name
	std::ifstream file("pricer.in");

	//if no value exists in the buffer
	if ((std::getline(file, line)))
	{
		readFromFile = true;
	}
	else if(std::getline(std::cin, line))
	{		
		readFromFile = false;
		std::cout << "Input error, no file \"pricer.in\" can be found. No string buffer data can be found" << std::endl;
		return -1;
	}

	DataManager dataManager(targetSize);

	do
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
					auto output = dataManager.getOutputData(tempOrder);
					outputFile.write(output.c_str(), output.length());
					dataManager.updateTargetSizeReached(tempOrderAction);
				}
			}

			//targetSize is no longer reached
			else if (dataManager.previousTargetSizeReached(tempOrderAction))
			{
				//output data
				auto output((std::to_string(tempOrder->m_timestamp) + " ") + (tempOrderAction + " NA\n"));
				outputFile.write(output.c_str(), output.length());
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
					auto output = dataManager.getOutputData(tempOrder);
					outputFile.write(output.c_str(), output.length());
					//set current price to previous price
					dataManager.updateTargetSizeReached(tempOrderAction);
				}
			}
			//targetSize is no longer reached
			else if (dataManager.previousTargetSizeReached(tempOrderAction))
			{
				//output data					
				auto output((std::to_string(tempOrder->m_timestamp) + " ") + ((tempOrderAction == 'B') ? "S NA\n" : "B NA\n"));
				outputFile.write(output.c_str(), output.length());
				//set current price to previous price
				dataManager.updateTargetSizeReached(tempOrderAction);
				dataManager.updatePrice(tempOrderAction);
			}
		}
	} //this loop will continue until the file is empry, or the buffer is empty
	while ((readFromFile) ? std::getline(file, line) : std::getline(std::cin, line));

	file.close();
	return 0;
}
