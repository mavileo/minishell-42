// 42 HEADER

#include "minishell.h"

int		main(int ac, char *av[], char *envp[])
{
	char *input;

	prompt();
	get_next_line(0, &input);
	return (0);
}
