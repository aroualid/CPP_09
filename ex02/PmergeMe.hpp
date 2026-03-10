#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include <deque>
#include <vector>
#include <cstdlib>
#include <limits>
#include <set>
#include <algorithm>

class PmergeMe {

public:
	PmergeMe();
	PmergeMe(PmergeMe const & src);
	~PmergeMe();
	PmergeMe &operator=(PmergeMe const & src); 
	int SortVector(int size);
	void MakePairsVector(int size);
//	void SwapElementsVector(int size, int i);
	std::vector<int> PushOnMain(int size, std::vector<int> v);




	std::vector<int> vec;
	std::vector<int> vmain;
	std::vector<int> vpend;
	std::vector<int> vlo;
	/*std::deque<int> deq;
	std::deque<int> dmain;
	std::deque<int> dpend;
	std::deque<int> dlo;
*/
};


