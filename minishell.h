// 42 HEADER

#ifndef MINISHELL_H
# define MINISHELL_H

#include <stdio.h>

#include "libft/libft.h"
#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <errno.h>
#include <string.h>
#include <sys/types.h>
#include <dirent.h>

#define BUFFER_SIZE 4096
#define TRUE 1
#define FALSE 0
#define	CMP_SYMBOLS "<>|;"
#define	SYMBOL_MAX_LEN 2
#define	SYMBOL_TABLE_FILE_LOCATION "input_to_token_list.c"
#define	REDIRECTIONS(type) type > 0 && type < 4 ? TRUE : FALSE

enum	e_token_type
{
	COMMAND,
	R_APPEND,
	R_TRUNC,
	R_IN,
	PIPE,
	SEMICOLON,
	AND,
	OR
};

typedef	struct	s_env
{
	char 			*name;
	char 			*value;
	struct s_env	*next;
}				t_env;

typedef struct		s_token
{
	enum e_token_type type;
	char **args;
}					t_token;

extern t_env	*env;

/* GENERAL */
void	prompt(void);
t_list	*input_to_token_list(char *input, void *env);
int     get_abs_value(char **args);

/* VARIABLES D'ENVIRONNEMENT */
int		add_env(char *name, char *value);
int		init_env(void);
t_env	*get_env(char *name);
char	*get_env_value(char *name);
int		actualise_env(char *name, char *value);
char	*replace_env_in_str(char *str);
void	*free_env(t_env *env);
void	*free_all_env(void);
int		check_path(char *path, int print);
int		get_abs_value(char **args);

/* BUILTINS */
int		ft_echo(char **args);
int 	ft_pwd(char **args);
int 	ft_cd(char **args);
int 	ft_export(char **args);
int 	ft_unset(char **args);
int 	ft_env(char **args);
int 	ft_exit(char **args);

/* TOKEN UTILS */
t_token		*ft_token_new(enum e_token_type type, char **args);
void		ft_token_free(t_token *token);
void		ft_print_token_list(t_list *l); // USELESS: ONLY FOR TEST

/* PARSING */

extern const char	*g_symbols_strs[6];

typedef	t_token	*(*t_add_token_function)(t_list **token_lst, t_list **e, t_token **current);

t_token		*add_command_token(t_list **token_lst, t_list **e, t_token **current);
t_token		*add_redirection_token(t_list **token_lst, t_list **e, t_token **current);
t_token		*add_pipe_token(t_list **token_lst, t_list **e, t_token **current);
t_token		*add_semicolon_token(t_list **token_lst, t_list **e, t_token **current);

char    *escape_expand(const char *str);

void        quotes_onoff(char *q, char c);

#endif
