# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mamuzamm <mamuzamm@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/04/01 20:33:09 by mamuzamm          #+#    #+#              #
#    Updated: 2025/07/01 22:25:06 by mamuzamm         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME       = push_swap
CC         = cc
CFLAGS     = -Wall -Wextra -Werror

LIBFT_DIR  = libft
LIBFT      = $(LIBFT_DIR)/libft.a

SRCS       = main.c move.c sort.c utils.c
OBJS       = $(SRCS:.c=.o)

RM         = rm -f

all: $(LIBFT) $(NAME)

$(LIBFT):
	@$(MAKE) -s -C $(LIBFT_DIR)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -L$(LIBFT_DIR) -lft -o $(NAME)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	$(RM) $(OBJS)
	$(MAKE) -s -C $(LIBFT_DIR) clean

fclean: clean
	$(RM) $(NAME)
	$(MAKE) -s -C $(LIBFT_DIR) fclean

re: fclean all

.PHONY: all clean fclean re
