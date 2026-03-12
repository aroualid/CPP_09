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
			if (val > std::numeric_limits<int>::max() || val < 0 )
			{
				std::cerr << "Error: invalid argument, too big or too low\n";
				return 0;
			} 
			std::set<int> set;
			for (int i = 1; av[i] != 0; i++)
			{
				if (set.count(atoi(av[i])))
				{
					std::cerr << "Error: twice the same number\n";
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
	PmergeMe Pme;
	std::cout << "Before:	";
	for (int i = 1; av[i]; i++)
		std::cout <<	av[i] << " ";
	std::cout << std::endl;
	for (int i = 1; av[i]; i++)
		Pme.vec.push_back(atoi(av[i]));
	for (int j = 1; av[j]; j++)
		Pme.deq.push_back(atoi(av[j]));

	t_time v;
	t_time d;
	v.start = std::clock();
	Pme.SortVector(2);
	v.end = std::clock();

	d.start = std::clock();
	Pme.SortDeque(2);
	d.end = std::clock();

	std::cout << "After:	";
	for (std::vector<int>::iterator it = Pme.vec.begin(); it != Pme.vec.end(); it++)
		std::cout << *it << " ";
	std::cout << std::endl;
	//std::cout << "After:	";
	//for (std::deque<int>::iterator it = Pme.deq.begin(); it != Pme.deq.end(); it++)
	//	std::cout << *it << " ";
	//std::cout << std::endl;
	std::cout << "Time to process a range of "<< ac - 1<< " elements with std::vector : ";
	std::cout << std::fixed << std::setprecision(5);
	std::cout << 1000.0 * (v.end - v.start) / CLOCKS_PER_SEC << "ms\n";
	std::cout << "Time to process a range of "<< ac - 1<< " elements with std::deque : ";
	std::cout << std::fixed << std::setprecision(5);
	std::cout << 1000.0 * (d.end - d.start) / CLOCKS_PER_SEC << "ms\n";
	/*
  std::cout << "vect : ";
	for (size_t z = 0; z < Pme.vec.size(); z++)
		std::cout << Pme.vec[z] << " ";
  std::cout << std::endl;

  std::cout << "deque : ";
	for (size_t z = 0; z < Pme.deq.size(); z++)
		std::cout << Pme.deq[z] << " ";
  std::cout << std::endl;*/
}
