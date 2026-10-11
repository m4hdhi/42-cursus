# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mamuzamm <mamuzamm@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2026/10/11 04:17:14 by mamuzamm          #+#    #+#              #
#    Updated: 2026/10/11 04:17:15 by mamuzamm         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = intern

CXX = c++
CXXFLAGS = -Wall -Wextra -Werror -std=c++98
RM = rm -rf

SRCS = ./main.cpp ./Bureaucrat.cpp ./AForm.cpp ./RobotomyRequestForm.cpp ./ShrubberyCreationForm.cpp ./PresidentialPardonForm.cpp ./Intern.cpp

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
