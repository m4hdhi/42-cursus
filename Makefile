# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mamuzamm <mamuzamm@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/07/03 20:16:45 by mamuzamm          #+#    #+#              #
#    Updated: 2025/08/30 11:22:56 by mamuzamm         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC     = cc
CFLAGS = -Wall -Wextra -Werror

MLX_PATH = minilibx
MLX_LIB  = $(MLX_PATH)/libmlx.a

NAME = fractol
SRC  = $(wildcard *.c)
OBJ  = $(SRC:.c=.o)

all: $(NAME)

$(NAME): $(OBJ) $(MLX_LIB)
	$(CC) $(CFLAGS) -o $@ $(OBJ) -L$(MLX_PATH) -lmlx -framework OpenGL -framework AppKit

%.o: %.c fractol.h
	$(CC) $(CFLAGS) -I. -I$(MLX_PATH) -c $< -o $@

$(MLX_LIB):
	$(MAKE) -C $(MLX_PATH)

clean:
	$(MAKE) -C $(MLX_PATH) clean
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
