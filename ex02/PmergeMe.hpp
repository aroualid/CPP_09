#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include <deque>
#include <vector>
#include <cstdlib>
#include <limits>
#include <set>

class PmergeMe {


public:
	PmergeMe();
	PmergeMe(PmergeMe const & src);
	~PmergeMe();
	PmergeMe &operator=(PmergeMe const & src); 
};

void MergeVector(std::vector<int> vec);

