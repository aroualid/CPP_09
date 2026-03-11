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

std::vector<int> PmergeMe::PushOnMain(int size, std::vector<int> v, int pair)
{
	std::vector<int>::iterator it = (v.begin()  + pair * size);

	while (*it)
	{
		vlo.push_back(*it);	
		it++;
	}
	int p = 0;
	std::vector<int> vp;
	for (int i = 0; i < size / 2; i++) // push on main b1;
	{
		vp.push_back(v[i]);
	}
	for (size_t k = size / 2; k < v.size(); k+=size) // push all a on main
	{
		if (p <  pair)
		{
			for (int j = 0; j < size / 2; j++)
				vp.push_back(v[j + k]);
			if (pair > 1)
			{
				for (int l = size/2; l < size; l++)
					vpend.push_back(v[l+k]);
			}
		}
		p++;	
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
	vlo.erase(vlo.begin(), vlo.end());	

	if (vec.size() / (size *2) < 1)
		vmain = PushOnMain(size, vec, pair);
	else
		vmain = PushOnMain(size, vmain, pair);

	std::cout << "_____________________________________________________________\n";
	std::cout << "Left over =    ";
	for (size_t l = 0; l < vlo.size(); l++)
		std::cout << vlo[l] << " ";
	std::cout << "\n";

	std::cout << "Pend =   ";
	for (size_t p = 0; p < vpend.size(); p++)
		std::cout << vpend[p] << " ";
	std::cout << "\n";

	vpend.erase(vpend.begin(), vpend.end());

	for (size_t z = 0; z < vmain.size(); z++)
	{
		if ((int)z == size / 2 || z == vmain.size() - vlo.size())
			std::cout << "| ";
        std::cout << vmain[z] << " ";
	}
	std::cout << std::endl;
	return 1;
}

