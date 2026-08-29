# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mamuzamm <mamuzamm@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2026/06/08 16:18:55 by mamuzamm          #+#    #+#              #
#    Updated: 2026/07/11 00:37:04 by mamuzamm         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME    = cub3D
CC      = cc
CFLAGS  = -Wall -Wextra -Werror -O2
INCS    = -I. -Ilibft -Iget_next_line -Iminilibx

LIBFT_DIR = libft
LIBFT     = $(LIBFT_DIR)/libft.a

MLX_DIR   = minilibx
MLX       = $(MLX_DIR)/libmlx.a

SRCS = \
	main.c \
	\
	core/init.c \
	core/cleanup.c \
	core/hooks.c \
	\
	utils/utils.c \
	\
	parse/cfg_error.c \
	\
	input/input_keys.c \
	input/input_move.c \
	input/input_collide.c \
	input/input_mouse.c \
	\
	render/render_put.c \
	render/render_columns.c \
	render/render_columns_fill.c \
	render/render_frame.c \
	render/render_ray.c \
	render/render_dda.c \
	\
	parse/parse_utils_a.c \
	parse/parse_utils_b.c \
	parse/parse_cfg.c \
	parse/parse_cfg_utils.c \
	parse/map_validate.c \
	parse/map_flood.c \
	parse/load_cub_a.c \
	parse/load_cub_finalize.c \
	parse/load_cub_b.c \
	parse/load_cub_b_helpers.c \
	\
	get_next_line/get_next_line.c \
	get_next_line/get_next_line_utils.c

OBJS = $(SRCS:.c=.o)

all: $(LIBFT) $(MLX) $(NAME)

$(LIBFT):
	@$(MAKE) -C $(LIBFT_DIR)

$(MLX):
	@$(MAKE) -C $(MLX_DIR)

$(NAME): $(OBJS) $(LIBFT) $(MLX)
	$(CC) $(CFLAGS) $(OBJS) $(LIBFT) $(MLX) \
		-lX11 -lXext -lm -o $@

%.o: %.c cub3d.h
	$(CC) $(CFLAGS) $(INCS) -c $< -o $@

clean:
	@rm -f $(OBJS)
	@$(MAKE) -C $(LIBFT_DIR) clean
	@$(MAKE) -C $(MLX_DIR) clean

fclean: clean
	@rm -f $(NAME)
	@$(MAKE) -C $(LIBFT_DIR) fclean

bonus: all

re: fclean all

.PHONY: all bonus clean fclean re
