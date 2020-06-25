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

#define BUFFER_SIZE 4096

enum	e_token_type
{
	COMMAND,
	REDIR1,
	REDIR2,
	REDIR3,
	PIPE,
	AND,
	OR
};

typedef struct		s_token
{
	enum e_token_type type;
	char **args;
}					t_token;

void		prompt(void);
t_token		*input_to_token_list(char *input, void *env);

#endif
