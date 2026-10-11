# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mamuzamm <mamuzamm@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2026/10/11 04:16:07 by mamuzamm          #+#    #+#              #
#    Updated: 2026/10/11 04:16:08 by mamuzamm         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = form

CXX = c++
CXXFLAGS = -Wall -Wextra -Werror -std=c++98
RM = rm -rf

SRCS = ./main.cpp ./Bureaucrat.cpp ./AForm.cpp ./RobotomyRequestForm.cpp ./ShrubberyCreationForm.cpp ./PresidentialPardonForm.cpp

OBJS = $(SRCS:.cpp=.o)

all: $(NAME)

$(NAME): $(OBJS)
	$(CXX) $(CXXFLAGS) $(OBJS) -o $(NAME)

clean:
	$(RM) $(OBJS)

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re
