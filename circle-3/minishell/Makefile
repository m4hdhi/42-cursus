# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mamuzamm <mamuzamm@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/10/10 07:53:13 by mamuzamm          #+#    #+#              #
#    Updated: 2026/01/29 04:20:08 by mamuzamm         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell

CC = cc
CFLAGS = -Wall -Wextra -Werror 
RM = rm -f

SRCS = 	minishell.c \
		paths.c \
		signals.c \
		init_shell.c \
		expansions/expansions.c \
		expansions/expansions_utils.c \
			execution/error.c \
			execution/gallows.c \
			execution/gallows_utils.c \
			execution/here_doc.c \
			execution/handle_nodes.c \
			execution/handle_utils.c \
				tree/free_ast.c \
				tree/tree_utils.c \
					helpers/ft_strchr.c \
					helpers/ft_strdup.c \
					helpers/ft_strlen.c \
					helpers/ft_strtrim.c \
					helpers/ft_substr.c \
					helpers/ft_strncmp.c \
					helpers/ft_strjoin.c \
					helpers/ft_split.c \
					helpers/ft_itoa.c \
						parsing/qoutes.c \
						parsing/splits.c \
						parsing/splits_utils.c \
						parsing/syntax.c \
						parsing/token_utils.c \
						parsing/tokenization.c \
						parsing/tokens_1.c \
						parsing/tokens_2.c \
		builtins/echo_cmd.c \
		builtins/pwd_cmd.c \
		builtins/cd_cmd.c \
		builtins/exit_cmd.c \
		builtins/env_cmd.c \
		builtins/unset_cmd.c \
		builtins/export_cmd.c \
			builtins/utils/unset_utils_1.c \
			builtins/utils/cd_utils_1.c \
			builtins/utils/cd_utils_2.c \
			builtins/utils/cd_utils_3.c \
			builtins/utils/cd_utils_4.c \
			builtins/utils/exit_utils_1.c \
			builtins/utils/export_utils_1.c \
			builtins/utils/export_utils_2.c \
			builtins/utils/export_utils_3.c \
			builtins/utils/export_utils_4.c \
			builtins/utils/export_utils_5.c \
			builtins/utils/export_utils_6.c \
				helpers/ft_atol.c \
				helpers/ft_memset.c \
				helpers/ft_strlcpy.c \
				helpers/ft_atoi.c \
				helpers/ft_calloc.c \
				helpers/ft_bzero.c \
				helpers/ft_lstclear.c \

OBJS = $(SRCS:.c=.o)
LDFLAGS = -lreadline 
READLINEFLAGS = -L/opt/vagrant/embedded/lib/ -Iopt/vagrant/embedded/include/readline

all:$(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(READLINEFLAGS) $^ -o $@ $(LDFLAGS)

%.o:%.c
	$(CC) $(CFLAGS) -c $< -o $@ 

clean: 
	$(RM) $(OBJS)

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re
