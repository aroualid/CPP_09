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
	/*
	for (size_t j = 0; j < vec.size(); j++)
	{
        std::cout << vec[j] << " ";
	}
	std::cout << std::endl;
	*/
}

std::vector<int> generateJacobsthalVec(int n) 
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

std::vector<int> buildInsertionOrderVec(int numPends) 
{
    std::vector<int> order;
    if (numPends == 0) 
			return order;

    std::vector<int> jacob = generateJacobsthalVec(numPends);
    int lastJacob = 1;

    order.push_back(1); 

    for (size_t i = 1; i < jacob.size(); ++i) 
	{
        int currentJacob = jacob[i];
        
        int start = (currentJacob > numPends) ? numPends : currentJacob;
        
        for (int j = start; j > lastJacob; --j)
            order.push_back(j);
        lastJacob = start;
        if (lastJacob == numPends) break;
    }
    return order;
}

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
    std::vector<int> order = buildInsertionOrderVec(vpend.size() / blockSize); 
    
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

    /*std::cout << "_____________________________________________________________\n";
    std::cout << "Left over =    ";
    for (size_t l = 0; l < vlo.size(); l++)
        std::cout << vlo[l] << " ";
    std::cout << "\n";

    std::cout << "Pend =   ";
    for (size_t p = 0; p < vpend.size(); p++)
        std::cout << vpend[p] << " ";
    std::cout << "\n";
		*/
    vpend.erase(vpend.begin(), vpend.end());

    vec = vmain; 
    
    for (size_t l = 0; l < vlo.size(); l++) 
        vec.push_back(vlo[l]);
		/*
    for (size_t z = 0; z < vmain.size(); z++)
        std::cout << vmain[z] << " ";
    std::cout << std::endl;
    */
    return 1;
}




void PmergeMe::MakePairsDeque(int size)
{
	int half = size / 2;
	for (int i = size -1; i < (int)deq.size(); i+=size)
	{
		if (deq[i - half] > deq[i]) 
			std::swap_ranges(deq.begin() + i - size + 1, deq.begin() + i - half + 1, deq.begin() + i - half + 1 );
	}
	/*
	for (size_t j = 0; j < deq.size(); j++)
	{
        std::cout << deq[j] << " ";
	}
	std::cout << std::endl;*/
}

std::deque<int> generateJacobsthalDeq(int n) 
{
    std::deque<int> jacob;
    jacob.push_back(1); 
    jacob.push_back(3); 
    
    while (jacob.back() < n) 
	{
        int next = jacob.back() + 2 * jacob[jacob.size() - 2];
        jacob.push_back(next);
    }
    return jacob;
}

std::deque<int> buildInsertionOrderDeq(int numPends) 
{
    std::deque<int> order;
    if (numPends == 0) 
			return order;

    std::deque<int> jacob = generateJacobsthalDeq(numPends);
    int lastJacob = 1;

    order.push_back(1); 

    for (size_t i = 1; i < jacob.size(); ++i) 
	{
        int currentJacob = jacob[i];
        
        int start = (currentJacob > numPends) ? numPends : currentJacob;
        
        for (int j = start; j > lastJacob; --j)
            order.push_back(j);
        lastJacob = start;
        if (lastJacob == numPends) break;
    }
    return order;
}

std::deque<int> PmergeMe::PushOnMain(int size, std::deque<int> v, int pair)
{
    std::deque<int> vp;
    int half = size / 2;
    
    dpend.clear();
    dlo.clear();

    for (int i = 0; i < half; i++)
        vp.push_back(v[i]); 
    for (int i = half; i < size; i++)
        vp.push_back(v[i]); 

    for (int i = 0; i < half; i++)
        dpend.push_back(v[i]);

    for (size_t k = size; k < (size_t)(pair * size); k += size)
    {
        for (int j = 0; j < half; j++)
            dpend.push_back(v[k + j]);             
        for (int j = half; j < size; j++)
            vp.push_back(v[k + j]); 
    }

    for (size_t i = pair * size; i < v.size(); i++) 
        dlo.push_back(v[i]);

    return vp;
}

int PmergeMe::SortDeque(int size)
{
    size_t pair = deq.size() / size;
    
    if (pair < 1)
        return 0;
    else
    {
        MakePairsVector(size);
        SortVector(size * 2);
    }
    
    dlo.erase(dlo.begin(), dlo.end());    

    dmain = PushOnMain(size, deq, pair);
    int blockSize = size / 2; 

    if (dlo.size() >= (size_t)blockSize)
		{
        for (int i = 0; i < blockSize; i++)
            dpend.push_back(dlo[i]);
        dlo.erase(dlo.begin(), dlo.begin() + blockSize);
    }
    std::deque<int> order = buildInsertionOrderDeq(dpend.size() / blockSize); 
    
    for (size_t i = 0; i < order.size(); ++i)
    {
        int pendIdx = order[i] - 1; 

        if (pendIdx <= 0 || pendIdx >= (int)(dpend.size() / blockSize)) 
            continue;
        int pendStart = pendIdx * blockSize;
        int pendEnd = pendStart + blockSize;
        
        int valueToCompare = dpend[pendEnd - 1]; 

        int left = 0;
        int right = (dmain.size() / blockSize) - 1;

        while (left <= right)
				{
            int mid = left + (right - left) / 2;
            
            if (dmain[(mid + 1) * blockSize - 1] < valueToCompare)
                left = mid + 1;
            else
                right = mid - 1;
        }
        dmain.insert(dmain.begin() + (left * blockSize), dpend.begin() + pendStart, dpend.begin() + pendEnd);
	}
	/*
    std::cout << "_____________________________________________________________\n";
    std::cout << "Left over =    ";
    for (size_t l = 0; l < dlo.size(); l++)
        std::cout << dlo[l] << " ";
    std::cout << "\n";

    std::cout << "Pend =   ";
    for (size_t p = 0; p < dpend.size(); p++)
        std::cout << dpend[p] << " ";
    std::cout << "\n";
	*/
    dpend.erase(dpend.begin(), dpend.end());

    deq = dmain; 
    
    for (size_t l = 0; l < dlo.size(); l++) 
        deq.push_back(dlo[l]);

    
    return 1;
}


