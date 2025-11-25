//#include "BitcoinExchange.hpp"
#include <iostream>
#include <fstream>
#include <string>

int main(int argc, char **av)
{
	if (argc == 2)
	{
		std::ifstream file(av[1]);
		std::string line;
		
		if (file.is_open())
		{
			while (std::getline(file,line))
			{
				std::cout << line << std::endl;
			}

		}
		else
			std::cout << "Error: could not open or read the file\n";
	}
	else
		std::cout << "Error: no file\n";
}

//ari[date] = valeur du bc a date
 
