# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mamuzamm <mamuzamm@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2026/10/25 03:26:46 by mamuzamm          #+#    #+#              #
#    Updated: 2026/10/25 03:26:48 by mamuzamm         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME     = convert
CXX      = c++
CXXFLAGS = -Wall -Wextra -Werror -std=c++98

SRC = main.cpp ScalarConverter.cpp
HDR = ScalarConverter.hpp
OBJ = $(SRC:.cpp=.o)

all: $(NAME)

$(NAME): $(OBJ)
	$(CXX) $(CXXFLAGS) $(OBJ) -o $(NAME)

%.o: %.cpp $(HDR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
