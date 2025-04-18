NAME = hotrace
CC  = cc
CFLAGS = -Wall -Wextra -Werror

SRCS = hotrace.c
OBJS = $(SRCS:.c=.o)

$(NAME) : $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME)

%.o: %.c hotrace.h
	$(CC) $(CFLAGS) -c $< -o $@
clean:
	rm -rf $(OBJS)
fclean: clean
	rm -rf $(NAME)
re: fclean $(NAME)