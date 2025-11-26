#include "BitcoinExchange.hpp"


int main(int argc, char **av)
{
	if (argc == 2)
	{
		std::ifstream file(av[1]);
		BitcoinExchange btc;
		
		if (file.is_open())
		{
			btc.fillData();	
			check_result(file, btc);
		}
		else
			std::cout << "Error: could not open or read the file\n";
	}
	else
		std::cout << "Error: no file\n";
}

 
