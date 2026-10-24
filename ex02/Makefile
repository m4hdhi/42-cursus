# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mamuzamm <mamuzamm@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2026/10/25 03:28:25 by mamuzamm          #+#    #+#              #
#    Updated: 2026/10/25 03:28:27 by mamuzamm         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME     = IdentifyType
CXX      = c++
CXXFLAGS = -Wall -Wextra -Werror -std=c++98

SRC = main.cpp Base.cpp
HDR = Base.hpp A.hpp B.hpp C.hpp
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
