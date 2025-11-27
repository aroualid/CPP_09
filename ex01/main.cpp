#include "RPN.hpp"

int main(int argc, char **av)
{
	if (argc == 2)
	{
		parse(av[1]);
	}
	else
		std::cerr << "Error: Wrong number of args\n";
}
