# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mamuzamm <mamuzamm@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/06/10 21:50:12 by mamuzamm          #+#    #+#              #
#    Updated: 2025/06/25 22:25:26 by mamuzamm         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAMEC        = client
NAMES        = server
BONUS_NAMEC  = client_bonus
BONUS_NAMES  = server_bonus

SRCC         = client.c
SRCS         = server.c
BONUSC       = client_bonus.c
BONUSS       = server_bonus.c

OBJC         = $(SRCC:.c=.o)
OBJS         = $(SRCS:.c=.o)
OBJBC        = $(BONUSC:.c=.o)
OBJBS        = $(BONUSS:.c=.o)

CC           = cc
CFLAGS       = -Wall -Wextra -Werror

all: $(NAMEC) $(NAMES)

$(NAMEC): $(OBJC)
	$(CC) $(CFLAGS) $^ -o $@

$(NAMES): $(OBJS)
	$(CC) $(CFLAGS) $^ -o $@

bonus: $(BONUS_NAMEC) $(BONUS_NAMES)

$(BONUS_NAMEC): $(OBJBC)
	$(CC) $(CFLAGS) $^ -o $@

$(BONUS_NAMES): $(OBJBS)
	$(CC) $(CFLAGS) $^ -o $@

clean:
	rm -f $(OBJC) $(OBJS) $(OBJBC) $(OBJBS)

fclean: clean
	rm -f $(NAMEC) $(NAMES) $(BONUS_NAMEC) $(BONUS_NAMES)

re: fclean all

.PHONY: all bonus clean fclean re
