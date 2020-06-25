// 42 HEADER

#include "minishell.h"

void	prompt(void)
{
	write(1, "$> ", ft_strlen("$> "));
}
