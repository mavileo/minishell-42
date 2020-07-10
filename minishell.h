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

/* rw = read/write, en attente d'un meilleur nom */
typedef struct		s_rw
{
	int fd1r;	
	int fd1w;	
	int fd2r;	
	int fd2w;	
}					t_rw;

/* VERSION avec un typedef sur int t_pipe[2]
#define read  0
#define write 1

typedef	int t_pipe[2];
typedef struct		s_rw
{
	t_pipe p1;
	t_pipe p2;
}					t_rw;
*/

extern t_env	*env;
extern int		(*g_builtins[]) ();
extern int		(*g_exec_token[]) ();
extern char		*builtins[];

typedef	int	(*t_exec_token_function)(t_list *token, t_rw *rw);

/* GENERAL */
void	prompt(void);
t_list	*input_to_token_list(char *input);
int     get_abs_value(char **args);
int		command_container(t_list *tokens_list);
t_list *get_next_token(t_list *tokens_list);

/* VARIABLES D'ENVIRONNEMENT */
int		add_env(char *name, char *value);
int		init_env(char *envp[]);
t_env	*get_env(char *name);
char	*get_env_value(char *name);
int		actualise_env(char *name, char *value);
char	*replace_env_in_str(char *str);
void	*free_env(t_env *env);
void	*free_all_env(void);
int		check_path(char *path, int print);
int		get_abs_value(char **args);
char	**env_to_envp(void);

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
char		*escape_expand(const char *str);
void        quotes_onoff(char *q, char c);

/* EXECUTION */
int			ft_command(t_list *token);
/* int			ft_r_append(t_list *token);
int			ft_r_trunc(t_list *token);
int			ft_r_in(t_list *token);
int			ft_pipe(t_list *token);
int			ft_semicolon(t_list *token);
int			ft_and(t_list *token);
int			ft_or(t_list *token); */

#endif
