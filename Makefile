NAME = minishell

MAIN = main.c

FLAGS = -Wall -Wextra -Werror

LIBS = minishlib.a libft/libft.a

#BUILTINS 

MINISHFCT = prompt.c get_input.c ft_display_error.c \
		token_utils.c 	\
		add_token_functions.c \
		input_to_token_list.c \
		escape_expand.c parsing_utils.c \
		env_funcs.c env_funcs2.c \
		path.c ft_cd.c \
		get_tokens.c \
		tokens_container.c commands_list.c \
		ft_echo.c \
		ft_pwd.c \
		ft_export.c ft_unset.c \
		ft_env.c ft_exit.c \
		ft_command.c ft_pipe.c fds.c ft_redirections.c signalhandlers.c

ALL_SRCS = $(MINISHFCT) # $(addprefix builtins/,$(BUILTINS))

OBJS = $(BUILTINS:.c=.o) $(MINISHFCT:.c=.o)

.PHONY: libft all
.SILENT: libft clean fclean re minishlib $(NAME)

all: $(NAME)

$(NAME) : libft minishlib
	gcc -g3 $(FLAGS) $(MAIN)  $(LIBS) -o $(NAME)

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
	gcc -g $(FLAGS) tests/tmp.c  $(LIBS) -o $(NAME)
