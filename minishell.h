// 42 HEADER

#ifndef MINISHELL_H
# define MINISHELL_H

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

typedef	struct	s_env
{
	char 			*name;
	char 			*value;
	struct s_env	*next;
}				t_env;

extern t_env	*env;

void    prompt(void);
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


#endif
