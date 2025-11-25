NAME = btc
CXX = c++
CXXFLAGS=  -Wall -Wextra -Werror -g3 -std=c++98 -MMD

OBJ_PATH = obj/
SRC = main.cpp BitcoinExchange.cpp 
OBJ_NAME = $(SRC:.cpp=.o)
OBJ = $(addprefix $(OBJ_PATH), $(OBJ_NAME))

.DEFAULT_GOAL := all

.PHONY: all clean fclean re 

$(NAME): $(OBJ)
	$(CXX) $(CXXFLAGS) -o $(NAME) $(OBJ)

$(OBJ_PATH)%.o:%.cpp
	mkdir -p $(@D)
	$(CXX) $(CXXFLAGS) -o $@ -c $<

-include $(OBJ:%.o=%.d)

all: $(NAME)

clean:
	rm -rf $(OBJ_PATH)

fclean: clean
	rm -rf $(NAME)

re:
	$(MAKE) fclean all
