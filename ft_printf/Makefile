NAME = libftprintf.a

CC = CC
CFLAGS = -Wall -Wextra -Werror 
SRCS = ft_printf.c utils.c
OBJS = $(SRCS:.c=.o)

all: $(NAME)


$(NAME): $(OBJS)
	ar -r $(NAME) $(OBJS)

%.o: %.c
	$(CC) $(CFLAGS) -c $<

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all  
