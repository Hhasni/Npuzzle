# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mdebelle <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2016/02/24 19:03:11 by mdebelle          #+#    #+#              #
#    Updated: 2016/02/24 19:03:12 by mdebelle         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #


NAME 		= n_puzzle

CXX			= g++
CXXFLAGS	= -Wall -Werror -Wextra -std=c++11

INC			= -I include
SRC			= Astar.cpp main.cpp Node.cpp
OBJ			= $(SRC:%.cpp=obj/%.o)

all: $(NAME)

$(NAME): obj $(OBJ)
	$(CXX) $(CXXFLAGS) -o $@ $(OBJ) $(LIB)

obj/%.o: src/%.cpp
	$(CXX) $(CXXFLAGS) $(INC) -o $@ -c $<

obj:
	mkdir -p obj

clean:
	rm -rf obj

fclean: clean
	rm -rf $(NAME)

re: fclean all

.PHONY: fclean all clean
