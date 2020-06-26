NAME = minishell

MAIN = main.c

FLAGS = -Wall -Wextra -Werror

LIBS = minishlib.a libft/libft.a

#BUILTINS 

MINISHFCT = prompt.c		\
			main.c			\
			ft_echo.c		\
			ft_pwd.c		\
			ft_cd.c			\
			ft_export.c		\
			ft_env.c		\
			env_funcs.c		\
			env_funcs2.c	\
			utils.c			\
			token_utils.c 	\
			input_to_token_list.c

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
