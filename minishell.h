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
#define	CMP_SYMBOLS "<>|;"
#define	SYMBOL_MAX_LEN 2
#define	SYMBOL_TABLE_FILE_LOCATION "input_to_token_list.c"

enum	e_token_type
{
	COMMAND,
	REDIR1,
	REDIR2,
	REDIR3,
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
void		prompt(void);
t_token		*input_to_token_list(char *input, void *env);
char	*ft_strjoin_free(char *s1, char *s2, int c);

/* VARIABLES D'ENVIRONNEMENT */
int		add_env(char *name, char *value);
int		init_env(void);
t_env	*get_env(char *name);
char	*get_env_value(char *name);
int		actualise_env(char *name, char *value);
char	*replace_env_in_str(char *str);
void	*free_env(t_env *env);
void	*free_all_env(void);

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

#endif
