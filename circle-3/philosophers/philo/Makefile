# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mamuzamm <mamuzamm@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/09/10 06:18:55 by mamuzamm          #+#    #+#              #
#    Updated: 2026/01/25 07:32:00 by mamuzamm         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME    = philo

CC      = cc
CFLAGS  = -Wall -Wextra -Werror -pthread -g

SRC     = main.c utils.c init.c threads.c monitor.c routine.c
OBJ     = $(SRC:.c=.o)

HEADER  = philo.h

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -o $(NAME)

%.o: %.c $(HEADER)
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
