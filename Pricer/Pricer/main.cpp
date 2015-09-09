/*Andrew Morales
*Pricer.exe is designed to take in a target-size and some log data and process it.
*the data is then returned to a log file titled "pricer.TARGET-SIZE.out" and stored
*at the source location of Pricer.exe.
*Pricer.exe is designed to take in a single command line argument when piping in cout
*data from another program.
*
*example:     ParentProgram.exe | Pricer.exe 200
*
*this will take in and process log entries one by one seperated by \n as they are in
*the provided log file "pricer.in"
*the second use case is a stadalone application that takes in two command line arguments.
*The first being target-size and the second being the filename/path.
*
*example:     Pricer.exe 200 pricer.in
*
*This will open the file pricer.in and process all the logs until it is completed and exits.
*/


#include <iostream>
#include <fstream>
#include <string>
#include <memory>
#include "DataManager.h"

int main(int argc, char *argv[])
{
	//bool to determine if we are reading from a file or buffered input
	bool readFromFile = false;
	int targetSize;
	std::string inFileName;

	//check for the correct arguments. Provide feedback for incorrect arguments
	switch (argc)
	{
	case 0:
	case 1:
		std::cout << "Missing arguments" << std::endl;
		return -1;

	case 3:
		//if we are given a filename, we will also set it here
		inFileName = argv[argc - 1];
		readFromFile = true;
	case 2:
		//set targetsize from command line argument
		try
		{
			targetSize = std::stoi(argv[1]);

		}
		//return if the arguments are backwards
		catch (std::exception e)
		{
			std::cout << "Invalid command line arguments. " << std::endl;
			std::cout << "target-size filename" << std::endl;
			return -1;
		}
		break;
	default:
		std::cout << "Invalid command line arguments" << std::endl;
		return -1;
	}

	//output file named according to the targetsize
	std::ofstream outputFile;
	std::string outFileName = "pricer." + std::to_string(targetSize) + ".out";
	outputFile.open(outFileName);

	//line is the temp value from string buffer, or file
	std::string line;
	std::ifstream file(inFileName);

	DataManager dataManager(targetSize);

	/*read from file or from std::cin depending on if the user has
	/*given us a filename as a command-line argument or not.
	*/
	while ((readFromFile) ? std::getline(file, line) : std::getline(std::cin, line))
	{
		//if the input is too small, we have not recieved a full line
		if (line.length()<8)
			return 0;

		//create an order with the string data and place it in a shared pointer.
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
					//set the current targetsize to the previous targetsize
					dataManager.updateTargetSizeReached(tempOrderAction);
				}
			}

			//targetSize is no longer reached
			else if (dataManager.previousTargetSizeReached(tempOrderAction))
			{
				//output data
				auto output((std::to_string(tempOrder->m_timestamp) + " ") + (tempOrderAction + " NA\n"));
				outputFile.write(output.c_str(), output.length());

				//set the current targetsize and price to the previous targetsize and price
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

					//set the current targetsize to the previous targetsize
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
	}

	file.close();
	return 0;
}
