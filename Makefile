NAME = minishell

MAIN = main.c

FLAGS = -Wall -Wextra -Werror

LIBS = minishlib.a libft/libft.a

#BUILTINS 

MINISHFCT = prompt.c input_to_token_list.c 

ALL_SRCS = $(MINISHFCT) # $(addprefix builtins/,$(BUILTINS))

OBJS = $(BUILTINS:.c=.o) $(MINISHFCT:.c=.o)

.PHONY: libft all
.SILENT: libft clean fclean re minishlib $(NAME)

all: $(NAME)

$(NAME) : libft minishlib
	gcc $(FLAGS) $(MAIN)  $(LIBS) -o $(NAME)

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
