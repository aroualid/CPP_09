
#ifndef BITCOINEXCHANGE_HPP
# define BITCOINEXCHANGE_HPP

#include <iostream>
#include <fstream>
#include <string>
#include <map>
#include <cstdlib>
class BitcoinExchange {

public:
	BitcoinExchange();
	BitcoinExchange(BitcoinExchange const & src);
	~BitcoinExchange();
	BitcoinExchange &operator=(BitcoinExchange const & src);
	void fillData();
	long dateFormat(std::string);
	void print_result(long, long double, std::string); 
//	void printTable();
private:
	std::map<int, std::string> table;
	/*int year;
	int month;
	int day;*/
};

void check_result(std::ifstream&, BitcoinExchange);

#endif
