NAME =		philo

SRCS =		src/philo.c		src/utils.c		src/init.c\
			src/monitor.c	src/validation.c

OBJS =		$(SRCS:.c=.o)

HEADER =	philo.h

CC = 		gcc

$(NAME) : $(OBJS) $(HEADER)
	$(MAKE) -C libft
	$(CC) $(OBJS) $(CFLAGS) libft/libft.a -o $(NAME)

all : $(NAME)

clean:
	$(MAKE) clean -C libft
	$(RM) $(OBJS)

fclean : clean
	$(MAKE) fclean -C libft
	$(RM) $(NAME)

re : fclean all

.PHONY: clean fclean re all
