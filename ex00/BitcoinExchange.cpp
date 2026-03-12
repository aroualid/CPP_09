
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
/*	year = src.year;
	month = src.month;
	day = src.month;
*/	
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
		std::cout << "Error : could not open or read the file\n";

}


int check_year(std::string year)
{
	if (year.length() == 4)
	{
		for (unsigned long i = 0; i < year.length(); i++)
		{
			if (isdigit(year[i]) == 0)
			{
				return (0);
			}
		}
		long year_long = std::atol(year.c_str());
		if (year_long < 2009)
		{
			std::cout << "Error : Bitcoin did not exist before 2009, try again \n";
			return (2);
		}
	}
	else
	{
		return (0);
	}
	return (1);
}

int check_month(std::string month)
{
	if (month.length() == 2)
	{
		for (unsigned long i = 0; i < month.length(); i++)
		{
			if (isdigit(month[i]) == 0)
			{
				return (0);
			}
		}
		long month_long = std::atol(month.c_str());
		if (month_long < 1 || month_long > 12)
		{
			return (0);
		}
	}
	else
	{
		return (0);
	}
	return (1);
}

int is_a_valid_day(long day, long month, long year)
{
	long max = 0;
	int err = 0;
	if (month == 2)
	{
		if ((year % 4 == 0 && year % 100 != 0)  || (year % 400 == 0))
		{
			max = 29;
			err = 2;
		}
		else
		{
			max = 28;
			err = 1;
		}
	}
	if (month == 4 || month == 6 || month == 9 || month == 11)
	{
		max = 30;
		err = 3;
	}
	if (day > max)
	{
		switch (err)
		{
			case 1: 
			{
				std::cout << "Error : not a leap year\n";
				return (0);			
			}
			case 2:
			{
				std::cout << "Error : a maximum of 29 days in February\n"; 
				return (0);
			}
			case 3:
			{
				std::cout << "Error : maximum 30 days in April, June, September and November\n";
				return (0);	
			}
		}
	}
	return (1);
}

int check_day(std::string day, std::string month, std::string year)
{
	if (day.length() == 2)
	{
		for (unsigned long i = 0; i < day.length(); i++)
		{
			if (isdigit(day[i]) == 0)
			{
				return (0);
			}
		}
		long day_long = std::atol(day.c_str());
		if (day_long < 0 || day_long > 31)
		{
			return (0);
		}
		long month_long = std::atol(month.c_str());
		long year_long = std::atol(year.c_str());
		if (year_long == 2009 && month_long == 1 && day_long == 1)
		{
			std::cout << "Error : Bitcoin did not exist before this date try again \n";
			return (2);
		}
		if (is_a_valid_day(day_long, month_long, year_long) == 0)
			return (2);
	}
	else
	{
		return (0);
	}
	return (1);
}

int check_date(std::string date)
{
	std::string year;
	std::string month;
	std::string day;
	size_t pos = date.find('-');
	if (pos != std::string::npos)
	{
		year = date.substr(0, pos);
		size_t pos2 = date.find('-', pos + 1);
		if (pos2 != std::string::npos)
		{
			month = date.substr(pos + 1, (pos2 - (pos + 1)));
			day = date.substr(pos2 + 1);
		}
		else	
			return (0);
	}		
	else	
		return (0);
	int y = check_year(year);
	if (y == 1)
	{
		int m = check_month(month);
		if (m == 1)
		{
			int d = check_day(day, month, year);
			if (d == 1)
				return (1);
			else if (d == 2)
			{
				return 2;
			}
			return (0);
		}
		else if (m == 2)
			return 2;
		return (0);
	}
	else if (y == 2)
	{
		return 2;
	}
	return (0);
			
}

int check_value(std::string value)
{
	if (value.empty())
	{
		std::cout << "Error : value is empty\n";
		return (0);
	}
	if (value[0] == '-')
	{
		std::cout << "Error : not a positive number\n";
		return (0);
	}
	for (unsigned long i = 0; i < value.length(); i++)
	{
		if (isdigit(value[i]) == 0 && (value[i] != '.'))
		{
			std::cout << "Error : not a valid value format\n";
			return (0);
		}
	}
	if (value.size() >= 4)
	{
		size_t t = value.find(".");
		if (t != value.npos)
		{
			if (t >= 4)
			{
				std::cout << "Error : too large a number \n";
				return (0);	
			}
		}
		if (t == value.npos)
		{
			if (value.size() == 4)
			{
				if (value[0] == '1' && value[1] == '0' && value[2] == '0' && value[3] == '0')
					;
				else
				{
					std::cout << "Error : too large a number \n";
					return (0);
				}
			}
			else
			{
				std::cout << "Error : too large a number \n";
				return (0);
			}

		}
	}
	return (1);
}

void BitcoinExchange::print_result(long date, long double value, std::string new_date)
{
	if (!table.count(date))
	{
		while (!table.count(date))
		{
			date--;
		}
	}
	for (int i = 0; i < 4; i++)
	{
	  std::cout << new_date[i];
	}
	std::cout << "-";
	for (int i = 4; i < 6; i++)
	{
	  std::cout << new_date[i];
	}
	std::cout << "-";
	for (int i = 6; i < 8; i++)
	{
	  std::cout << new_date[i];
	}
	std::cout << " => ";
	std::cout << value << " = ";
	double long res = strtold(table[date].c_str(), NULL);
	std::cout << res * value /*<< " [ " << date << " | " << table[date] << " ] "*/ << std::endl;


	//std::cout << table[date] << std::endl;
	
}

void check_result(std::ifstream& file, BitcoinExchange btc)
{
	std::string line;
	std::string date;
	std::string value;
	
	std::getline(file,line);
	while (std::getline(file,line))
	{
		if (line.empty())
			continue ;
		size_t pos = line.find('|');
		if (pos != line.npos)
		{
			if (pos + 2 < line.size() && pos - 1 > 0)
			{
				date = line.substr(0, pos - 1);
				value = line.substr(pos + 2);
				int c = check_date(date);
				if (c == 1)
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
					if (check_value(value) == 1)
					{
						long double new_value = strtold(value.c_str(), NULL);
						btc.print_result(res, new_value, new_date);
					}
				}
				else if (c == 0)
					std::cout << "Error : bad input => " << line << std::endl;	
			}
			else
				std::cout << "Error : bad input => " << line << std::endl;	
		}
		else
			std::cout << "Error : bad input => " << line << std::endl;	
//		else
//			std::cout << "non\n";
	}
}

/*void BitcoinExchange::printTable()
{
    std::map<int, std::string>::const_iterator it;

    for (it = this->table.begin(); it != this->table.end(); ++it)
    {
        std::cout << "Clé : " << it->first
                  << " | Valeur : " << it->second << std::endl;
    }

    std::cout << "---------------------------------------------" << std::endl;
}*/
