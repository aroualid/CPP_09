#include "PmergeMe.hpp"

PmergeMe::PmergeMe()
{}

PmergeMe::~PmergeMe()
{}

PmergeMe::PmergeMe(PmergeMe const & src)
{
	*this = src;
}

PmergeMe& PmergeMe::operator=(PmergeMe const & src)
{
	(void) src;
	return(*this);
}
/*
void PmergeMe::SwapElementsVector(int size, int i)
{
	for (int j = i - size; j < i /2; j++)
	{
		int temp = vec[j];
		vec[j] = vec[j+ size];
		vec[j+size] = temp;
	}
}*/

void PmergeMe::MakePairsVector(int size)
{
	std::cout << size << std::endl;
	int half = size / 2;
	for (int i = size -1; i < (int)vec.size(); i+=size)
	{
		if (vec[i - half] > vec[i]) 
		{

			std::swap_ranges(vec.begin() + i - size + 1, vec.begin() + i - half + 1, vec.begin() + i - half + 1 );
		}
	}
	for (size_t j = 0; j < vec.size(); j++)
	{
        std::cout << vec[j] << " ";
	}
	std::cout << std::endl;
}

	

int PmergeMe::SortVector(int size)
{
	size_t pair = vec.size() / size;
	if (pair < 1)
		return 0;
	else
	{
		MakePairsVector(size);
		SortVector(size *2);
	}
	return 1;
		

}
