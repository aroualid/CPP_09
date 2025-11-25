#include "BitcoinExchange.hpp"


int main(int argc, char **av)
{
	if (argc == 2)
	{
		std::ifstream file(av[1]);
		std::string line;
		
		BitcoinExchange btc;
		
		if (file.is_open())
		{
			btc.fillData();	
			/*while (std::getline(file,line))
			{				
				std::cout << line << std::endl;
			}*/
			btc.printTable();

		}
		else
			std::cout << "Error: could not open or read the file\n";
	}
	else
		std::cout << "Error: no file\n";
}

//ari[date] = valeur du bc a date
 
