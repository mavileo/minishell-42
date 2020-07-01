// 42 HEADER

#include "minishell.h"

void		quotes_onoff(char *q, char c)
{
	if ((c == 39 || c == '"') && *q == 0)
		*q = c;
	else if ((c == 39 && *q == 39) || (c == '"' && *q == '"'))
		*q = 0;
}
