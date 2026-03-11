#pragma once

#include <iomanip>
#include <iostream>
#include <fstream>
#include <string>
#include <deque>
#include <vector>
#include <cstdlib>
#include <limits>
#include <set>
#include <algorithm>
#include <ctime>

typedef struct s_time
{
	std::clock_t start;
	std::clock_t end;
} t_time;

class PmergeMe {

public:
	PmergeMe();
	PmergeMe(PmergeMe const & src);
	~PmergeMe();
	PmergeMe &operator=(PmergeMe const & src); 
	int SortVector(int size);
	void MakePairsVector(int size); 
	std::vector<int> PushOnMain(int size, std::vector<int> v, int pair);

	int SortDeque(int size);
	void MakePairsDeque(int size);
	std::deque<int> PushOnMain(int size, std::deque<int> v, int pair);


	std::vector<int> vec;
	std::vector<int> vmain;
	std::vector<int> vpend;
	std::vector<int> vlo;

	std::deque<int> deq;
	std::deque<int> dmain;
	std::deque<int> dpend;
	std::deque<int> dlo;

};


