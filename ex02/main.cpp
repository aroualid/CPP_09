#include "PmergeMe.hpp"


int check_args(int ac, char **av)
{
	if (ac < 3)
		return 0;
	else
	{
		for (int i = 1; i < ac; i++)
		{
			for (int j = 0; av[i][j] != 0; j++)
			{
				if (!isdigit(av[i][j]))
				{
					std::cerr << "Error: invalid argument, not a number\n";
					return 0;
				}
			}
			long val = atol(av[i]);
			if (val > std::numeric_limits<int>::max() || val <= 0 )
			{
				std::cerr << "Error: invalid argument, too big or too low\n";
				return 0;
			} 
}



int main(int ac, char **av)
{
	
}
