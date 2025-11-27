
#ifndef RPN_HPP
# define RPN_HPP

#include <iostream>
#include <fstream>
#include <string>
#include <stack>
#include <cstdlib>
#include <limits.h>

class RPN {

public:
	RPN();
	RPN(RPN const & src);
	~RPN();
	RPN &operator=(RPN const & src);

private:
};

void parse(std::string);

#endif
