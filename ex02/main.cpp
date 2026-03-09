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
			std::set<int> set;
			for (int i = 1; av[i] != 0; i++)
			{
				if (set.count(atoi(av[i])))
				{
					std::cerr << "Error: twice the same numberr\n";
					return 0;
				}
				set.insert(atoi(av[i]));
			}
		}
	}
	return (1);
}

int main(int ac, char **av)
{
	if (check_args(ac, av) == 0)
		return 0;
	std::vector<int> vec;
	std::deque<int> deq;

	for (int i = 1; av[i]; i++)
		vec.push_back(atoi(av[i]));
	for (int j = 1; av[j]; j++)
		vec.push_back(atoi(av[j]));
}
