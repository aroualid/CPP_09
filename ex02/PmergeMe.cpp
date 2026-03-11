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
			std::swap_ranges(vec.begin() + i - size + 1, vec.begin() + i - half + 1, vec.begin() + i - half + 1 );
	}
	for (size_t j = 0; j < vec.size(); j++)
	{
        std::cout << vec[j] << " ";
	}
	std::cout << std::endl;
}

std::vector<int> generateJacobsthal(int n) 
{
    std::vector<int> jacob;
    jacob.push_back(1); 
    jacob.push_back(3); 
    
    while (jacob.back() < n) 
	{
        int next = jacob.back() + 2 * jacob[jacob.size() - 2];
        jacob.push_back(next);
    }
    return jacob;
}

std::vector<int> buildInsertionOrder(int numPends) 
{
    std::vector<int> order;
    if (numPends == 0) 
		return order;

    std::vector<int> jacob = generateJacobsthal(numPends);
    int lastJacob = 1;

    // Le premier pend (P1) est traité à part ou inséré en premier
    order.push_back(1); 

    for (size_t i = 1; i < jacob.size(); ++i) 
	{
        int currentJacob = jacob[i];
        
        // On part du nombre de Jacobsthal actuel (borné par le nombre de pends)
        int start = (currentJacob > numPends) ? numPends : currentJacob;
        
        // On redescend jusqu'au dernier nombre de Jacobsthal traité
        for (int j = start; j > lastJacob; --j)
            order.push_back(j);
        lastJacob = start;
        if (lastJacob == numPends) break;
    }
    return order;
}
/*
std::vector<int> PmergeMe::PushOnMain(int size, std::vector<int> v, int pair)
{
	int p = 0;
	std::vector<int> vp;
	for (int i = 0; i < size / 2; i++) // push on main b1;
		vp.push_back(v[i]);
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
	std::vector<int>::iterator it = (v.begin()  + vp.size() + vpend.size());

	while (*it < (int)v.size())
	{
		vlo.push_back(*it);	
		it++;
	}
	if (vpend.empty())
	{
		for (size_t z = 0; z < vlo.size(); z++)
			vp.push_back(vlo[z]);
	}	
	return vp;
}
*/

std::vector<int> PmergeMe::PushOnMain(int size, std::vector<int> v, int pair)
{
    std::vector<int> vp;
    int half = size / 2;
    
    vpend.clear();
    vlo.clear();

    for (int i = 0; i < half; i++)
        vp.push_back(v[i]); 
    for (int i = half; i < size; i++)
        vp.push_back(v[i]); 

    for (int i = 0; i < half; i++)
        vpend.push_back(v[i]);

    for (size_t k = size; k < (size_t)(pair * size); k += size)
    {
        for (int j = 0; j < half; j++)
            vpend.push_back(v[k + j]);             
        for (int j = half; j < size; j++)
            vp.push_back(v[k + j]); 
    }

    for (size_t i = pair * size; i < v.size(); i++) 
        vlo.push_back(v[i]);

    return vp;
}

/*

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
	if (!vpend.empty())
	{
		std::cout << "PEND : ";
		for (size_t i = 0; i < vpend.size(); i++)
			std::cout << vpend[i] << " ";
		std::cout << std::endl;
	}
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
        std::cout << vmain[z] << " ";
	std::cout << std::endl;
	return 1;
}
*/

int PmergeMe::SortVector(int size)
{
    size_t pair = vec.size() / size;
    
    if (pair < 1)
        return 0;
    else
    {
        MakePairsVector(size);
        SortVector(size * 2);
    }
    
    vlo.erase(vlo.begin(), vlo.end());    

    vmain = PushOnMain(size, vec, pair);
    int blockSize = size / 2; 

    if (vlo.size() >= (size_t)blockSize)
	{
        for (int i = 0; i < blockSize; i++)
            vpend.push_back(vlo[i]);
        vlo.erase(vlo.begin(), vlo.begin() + blockSize);
    }
    std::vector<int> order = buildInsertionOrder(vpend.size() / blockSize); 
    
    for (size_t i = 0; i < order.size(); ++i)
    {
        int pendIdx = order[i] - 1; 

        if (pendIdx <= 0 || pendIdx >= (int)(vpend.size() / blockSize)) 
            continue;
        int pendStart = pendIdx * blockSize;
        int pendEnd = pendStart + blockSize;
        
        int valueToCompare = vpend[pendEnd - 1]; 

        int left = 0;
        int right = (vmain.size() / blockSize) - 1;

        while (left <= right)
		{
            int mid = left + (right - left) / 2;
            
            if (vmain[(mid + 1) * blockSize - 1] < valueToCompare)
                left = mid + 1;
            else
                right = mid - 1;
        }

        vmain.insert(vmain.begin() + (left * blockSize), vpend.begin() + pendStart, vpend.begin() + pendEnd);
	}

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

    vec = vmain; 
    
    for (size_t l = 0; l < vlo.size(); l++) 
        vec.push_back(vlo[l]);

    for (size_t z = 0; z < vmain.size(); z++)
        std::cout << vmain[z] << " ";
    std::cout << std::endl;
    
    return 1;
}
