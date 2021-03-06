/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mavileo <mavileo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/25 05:46:55 by mavileo           #+#    #+#             */
/*   Updated: 2020/07/25 05:52:43 by mavileo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>

# include "libft/libft.h"
# include <unistd.h>
# include <stdlib.h>
# include <fcntl.h>
# include <sys/stat.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <errno.h>
# include <string.h>
# include <sys/types.h>
# include <dirent.h>
# include <signal.h>

# define BUFFER_SIZE 4096
# define TRUE 1
# define FALSE 0
# define CMP_SYMBOLS "<>|;"
# define SYMBOL_MAX_LEN 2
# define SYNTAX_ERROR_CODE "2"

enum				e_token_type
{
	COMMAND = 0,
	R_APPEND,
	R_TRUNC,
	R_INPUT,
	PIPE,
	SEMICOLON,
};

typedef	struct		s_env
{
	char			*name;
	char			*value;
	struct s_env	*next;
}					t_env;

typedef struct		s_token
{
	enum e_token_type	type;
	char				**args;
}					t_token;

typedef	int			t_pipe[2];

typedef struct		s_fds
{
	int				save_stdin;
	int				save_stdout;
	t_pipe			pipe;
}					t_fds;

extern t_env		*g_env;
extern t_list		*g_process_pids;
extern int			(*g_builtins[]) ();
extern int			(*g_exec_token[]) ();
extern char			*g_builtins_list[];

int					*aaintptr(int v);
void				handle_ctrl_c(int i);
void				handle_ctrl_bs(int i);
void				save_process_pid(int pid);
void				ft_dsplerr(char *arg, char *error_msg);
char				*get_input(void);
void				prompt(void);
t_list				*input_to_token_list(char *input);
t_list				*get_first_token(t_list *tokens_list);
t_list				*get_next_semicolon(t_list *token);
t_list				*get_next_pipe(t_list *token);
t_list				*get_next_redirection(t_list *token);
t_list				*get_next_command(t_list *token);
t_list				*get_next_token(t_list *token);
char				*build_path(char *s1, char *s2);
int					add_env(char *name, char *value);
int					init_env(char *envp[]);
t_env				*get_env(char *name);
char				*get_env_value(char *name);
int					actualise_env(char *name, char *value);
char				*replace_env_in_str(char *str);
void				*free_env(t_env *env);
void				*free_all_env(void);
int					check_path(char *path, int print);
char				*get_abs_value(char *cmd);
char				**env_to_envp(void);
int					ft_echo(char **args);
int					ft_pwd(char **args);
int					ft_cd(char **args);
int					ft_export(char **args);
int					ft_unset(char **args);
int					ft_env(char **args);
int					ft_exit(char **args);
t_token				*ft_token_new(enum e_token_type type, char **args);
void				ft_token_free(void *token);
int					tokens_container(t_list *tokens_list);
t_token				*ft_token_dup(t_token *src);
extern const char	*g_symbols_strs[6];
typedef	t_token		*(*t_add_token_function)(t_list **token_lst, t_list **e,
					t_token **current);
t_token				*add_command_token(t_list **token_lst, t_list **e,
					t_token **current);
t_token				*add_redirection_token(t_list **token_lst, t_list **e,
					t_token **current);
t_token				*add_pipe_token(t_list **token_lst, t_list **e,
					t_token **current);
t_token				*add_semicolon_token(t_list **token_lst, t_list **e,
					t_token **current);
char				*escape_expand(const char *str);
void				quotes_onoff(char *q, char c);
t_fds				*init_fds(void);
int					ft_command(t_list *token, t_fds *fds);
int					ft_pipe(t_list *token, t_fds *fds);
int					ft_r_append(t_list *token, t_fds *fds);
int					ft_r_trunc(t_list *token, t_fds *fds);
int					ft_r_input(t_list *token, t_fds *fds);
t_list				*retrieve_command(t_list *token);
t_list				*commands_list(t_list *tokens);
void				execute_commands(t_list *commands);
char				is_redirection(enum e_token_type type);

#endif
