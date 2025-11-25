
#include "BitcoinExchange.hpp"

BitcoinExchange::BitcoinExchange()
{}

BitcoinExchange::~BitcoinExchange()
{}

BitcoinExchange::BitcoinExchange(BitcoinExchange const & src)
{
	*this = src;
}

BitcoinExchange& BitcoinExchange::operator=(BitcoinExchange const & src)
{
	table = src.table;
	return (*this);
}


long BitcoinExchange::dateFormat(std::string date)
{
	long res;
	std::string new_date;
	for (size_t i = 0; i < date.length(); i++)
	{
		if (date[i] != '-') {
            new_date += date[i];
        }
    }
	res = std::atol(new_date.c_str());
	return(res);
}

void BitcoinExchange::fillData()
{
	std::ifstream data("data.csv");
	std::string line;
	std::string date;
	std::string value;

	if (data.is_open())
	{
		while (std::getline(data,line))
		{
			size_t pos = line.find(',');
			date = line.substr(0, pos);
			value = line.substr(pos + 1);
			long res = dateFormat(date);
			this->table[res] = value;	
		}
	}
	else
		std::cout << "Error: could not open or read the file\n";

}

void BitcoinExchange::printTable()
{
    //std::cout << "--- Contenu de la Table de Taux de Change ---" << std::endl;
    
    // Déclaration d'un itérateur pour la map
    // Note : En C++98, on utilise std::map<...>::iterator ou std::map<...>::const_iterator
    // car 'auto' n'est pas disponible.
    std::map<int, std::string>::const_iterator it;

    // Boucle de parcours de la map du début à la fin
    for (it = this->table.begin(); it != this->table.end(); ++it)
    {
        // it->first est la clé (le 'int')
        // it->second est la valeur (le 'std::string')
        
        // On suppose que la clé 'int' est un format de date (AAAAJJMJ) ou similaire,
        // et la valeur 'std::string' est le taux de change.
        std::cout << "Clé : " << it->first
                  << " | Valeur : " << it->second << std::endl;
    }

    std::cout << "---------------------------------------------" << std::endl;
}
