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

void PmergeMe::MakePairsVector(int size)
{
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

std::vector<int> PmergeMe::PushOnMain(int size, std::vector<int> v)
{
	std::vector<int> vp;
	for (int i = 0; i < size / 2; i++) // push on main b1;
	{
		vp.push_back(v[i]);
	}
	for (size_t k = size / 2; k < v.size(); k+= size) // push all a on main
	{
		std::cout << "k = " << k << " | v[k] = " << v[k] << " | size = " << size << std::endl;
		for (int j = k; j < size; j++)
		{
			vp.push_back(v[j]);
		}
	}
	for (size_t z = 0; z < vlo.size(); z++)
		vp.push_back(vlo[z]);
	return vp;
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
	std::vector<int>::iterator it = (vec.begin()  + pair * size);
	vlo.erase(vlo.begin(), vlo.end());	
	while (*it)
	{
		vlo.push_back(*it);	
		it++;
	}
	if (vec.size() / (size *2) < 1)
		vmain = PushOnMain(size, vec);
	else
		vmain = PushOnMain(size, vmain);
	for (size_t z = 0; z < vmain.size(); z++)
	{
		if ((int)z == size / 2 || z == vmain.size() - vlo.size())
			std::cout << "| ";
        std::cout << vmain[z] << " ";
	}
	std::cout << std::endl;
	return 1;
}

