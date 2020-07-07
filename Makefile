NAME = minishell

MAIN = main.c

FLAGS = -Wall -Wextra -Werror

LIBS = minishlib.a libft/libft.a

#BUILTINS 

MINISHFCT = prompt.c		\
			token_utils.c 	\
			add_token_functions.c \
			input_to_token_list.c \
			escape_expand.c parsing_utils.c \
			env_funcs.c	env_funcs2.c \
			path.c ft_cd.c
#			ft_echo.c		\ 
#			ft_pwd.c		\
#			ft_export.c		\
#			ft_env.c		\

ALL_SRCS = $(MINISHFCT) # $(addprefix builtins/,$(BUILTINS))

OBJS = $(BUILTINS:.c=.o) $(MINISHFCT:.c=.o)

.PHONY: libft all
.SILENT: libft clean fclean re minishlib $(NAME)

all: $(NAME)

$(NAME) : libft minishlib
	gcc -g $(FLAGS) $(MAIN)  $(LIBS) -o $(NAME)

libft:
	cd libft/ && make -s && make -s clean

minishlib : libft
	gcc $(FLAGS) -c $(ALL_SRCS) -I./
	ar rc minishlib.a $(OBJS)
	ranlib minishlib.a
	make -s clean

clean:
		rm -f $(OBJS)
		cd libft/ && make -s clean

fclean: clean
		rm -f $(NAME)
		rm -f minishlib.a *.out *.gch
		cd libft/ && make -s fclean

re: fclean all

parsing: libft minishlib
	gcc -g $(FLAGS) main_parsing.c  $(LIBS) -o $(NAME)

tests: libft minishlib
	gcc -g $(FLAGS) tmp.c  $(LIBS) -o $(NAME)

