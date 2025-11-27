
#include "RPN.hpp"
#include <climits>

RPN::RPN()
{}

RPN::~RPN()
{}

RPN::RPN(RPN const & src)
{
	*this = src;
}

RPN& RPN::operator=(RPN const & src)
{
	(void) src;
	return(*this);
}

bool is_operator(char  c)
{
	if(c == '+' || c == '-' || c == '/' || c == '*')
		return (1);
	else
		return (0);
	
}

bool count_all(std::string av)
{
	int count_num = 0;
	int count_op = 0;
	
	size_t i = 0;
	while (i < av.length())
	{
		if (std::isspace(av[i]) != 0)
			i++;
		else if (std::isdigit(av[i]) != 0)
		{
			count_num++;
			i++;
		}
		else if(is_operator(av[i]) == 1)
		{
			count_op++;
			i++;
		}
		else
		{
			std::cerr << "Error : not a digit or an operator !\n";
			return (0);
		}
	}
	if (count_num == count_op + 1)
		return(1);
	else
	{
		std::cerr << "Error : wrong number of operator or digit \n";
		return (0);
	}
}

bool apply_op(std::stack<int> &st, char c)
{
	long first;
	long second;
	long res;
	if (st.size() < 2)
	{
		std::cerr << "Error: wrong amount of number\n";
		return (0);
	}
	else
	{
		first = st.top();
		st.pop();
		second = st.top();
		st.pop();
		switch(c)
		{
			case '+':
			{
				res = first + second;
				if (res >= INT_MAX || res <= INT_MIN)
				{	
					std::cerr << "Error : addition result is too high or too low\n";
					return (0);
				}
				//std::cout << "res = " << res << std::endl;
				st.push(res);
				return (1);
			}
			case '-':
			{
				res = second - first;
				if (res >= INT_MAX || res <= INT_MIN)
				{	
					std::cerr << "Error : subtraction result is too high or too low\n";
					return (0);
				}
				//std::cout << "res = " << res << std::endl;
				st.push(res);
				return (1);
			}
			case '*':
			{
				res = first * second;
				if (res >= INT_MAX || res <= INT_MIN)
				{	
					std::cerr << "Error : multiplication result is too high or too low\n";
					return (0);
				}
				//std::cout << "res = " << res << std::endl;
				st.push(res);
				return (1);
			}
			case '/':
			{
				if (first == 0)
				{
					std::cerr << "Error : no division by zero\n";
					return (0);
				}
				res = second / first;
				if (res >= INT_MAX || res <= INT_MIN)
				{	
					std::cerr << "Error : division result is too high or too low\n";
					return (0);
				}
				//std::cout << "res = " << res << std::endl;
				st.push(res);
				return (1);
			}
		}
	}
	return (0);
}

void parse(std::string av)
{
	std::stack<int> st;
	if (count_all(av) == 1)
	{
		size_t i = 0;
		while (i < av.length())
		{
			if (std::isdigit(av[i]) != 0)
			{
				st.push(av[i] - '0');
				i++;
			}
			else if (is_operator(av[i]) == 1)
			{
				if (apply_op(st, av[i]) == 0)
				{
					return ;
				}
				i++;

			}
			else
				i++;

		}
		std::cout << st.top() << std::endl;
	}
	//st.pop();
}
