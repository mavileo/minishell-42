NAME = libft.a

FLAGS = -Wall -Wextra -Werror

SRCS = 	ft_memset.c \
		ft_bzero.c \
		ft_memcpy.c \
		ft_memccpy.c \
		ft_memmove.c \
		ft_memchr.c \
		ft_memcmp.c \
		ft_strlen.c ft_index.c ft_indexr.c \
		ft_isalpha.c \
		ft_isdigit.c \
		ft_isalnum.c \
		ft_isascii.c \
		ft_isprint.c \
		ft_toupper.c \
		ft_tolower.c \
		ft_strchr.c ft_strrchr.c \
		ft_strcmp.c ft_strncmp.c \
		ft_strlcpy.c \
		ft_strlcat.c \
		ft_strnstr.c \
		ft_atoi.c \
		ft_calloc.c \
		ft_strdup.c \
		ft_substr.c \
		ft_strjoin.c ft_strjoin_free.c ft_reassign.c \
		ft_strtrim.c \
		ft_split.c \
		ft_itoa.c \
		ft_strmapi.c \
		ft_putchar_fd.c ft_putstr_fd.c ft_putendl_fd.c ft_putnbr_fd.c \
		ft_putstr.c \
		ft_lstnew.c ft_lstprint.c \
		ft_lstadd_front.c ft_lstadd_back.c ft_lstinsert.c ft_lstremove.c \
		ft_lstsize.c \
		ft_lstlast.c ft_lstfirst.c \
		ft_lstdelone.c \
		ft_lstclear.c \
		ft_lstiter.c \
		ft_lstmap.c \
		ft_tabfree.c ft_tabindex.c ft_tabpush.c ft_tabdup.c \
		get_next_line.c

HEADER = libft.h

OBJS = $(SRCS:.c=.o)

$(NAME): $(SRCS)
		gcc $(FLAGS) -c $(SRCS) -I./ $(HEADER)
		ar rc $(NAME) $(OBJS)
		ranlib $(NAME)

all: $(NAME)

clean:
		rm -f $(OBJS) *.gch

fclean: clean
		rm -f $(NAME)

re: fclean all


norme:
	norminette $(SRCS) $(HEADER)
