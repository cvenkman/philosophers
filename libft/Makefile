NAME =	libft.a

SRCS = 	ft_isprint.c		ft_strlen.c\
		ft_isdigit.c		ft_strlcpy.c\
		ft_isalnum.c		ft_strncmp.c\
		ft_isalpha.c		ft_tolower.c\
		ft_isascii.c		ft_toupper.c\
		ft_bzero.c			ft_strchr.c		ft_strrchr.c\
		ft_atoi.c			ft_strchr.c\
		ft_calloc.c			ft_strdup.c		ft_itoa.c\
		ft_strnstr.c		ft_substr.c\
		ft_putchar_fd.c		ft_putstr_fd.c	ft_putendl_fd.c\
		ft_putnbr_fd.c		ft_strjoin.c\
		ft_split.c			ft_strtrim.c	ft_strstr.c\
		ft_strcpy.c			ft_strcmp.c		errors.c

OBJS =		$(SRCS:.c=.o)

$(NAME): $(OBJS)
		ar rcs $(NAME) $(OBJS)

all: $(NAME)

clean:
		$(RM) $(OBJS)

fclean:  clean
		$(RM) $(NAME)

re:   fclean $(NAME)

.PHONY: all clean fclean re