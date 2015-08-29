#include <iostream>
#include <fstream>
#include <string>

int main(int argc, char *argv[])
{
	//TODO: fix hard coded value
	std::ifstream file("pricer1.in");

	for (int i = 0;i < argc;++i)
	{
		std::cout << argv[i] << std::endl;
	}

	//TODO: utalize the command line argument instead of this hard-coded int target-size
	int targetSize = std::stoi(argv[3]);

	//holds the current line being read from the .in file
	std::string line;

	file.is_open();
	std::cout << "file.is_open() " << file.is_open() << std::endl;

	if (file)
	{
		getline(file, line);
	}
	
	std::cin.get();
	return 0;
}
