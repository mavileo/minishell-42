// 42 HEADER

#include "minishell.h"

char	*escape_expand(const char *str)
{
	char *s;
	unsigned int i;
	char q;

	q = 0;
	i = 0;
	s = ft_strdup(str);
	while (s[i])
	{
		quotes_onoff(&q, s[i]);
		if (s[i] == '"' || s[i] == '\'')
		{
			ft_memmove(&s[i], &s[i + 1], ft_strlen(s) - i);
			i--;
		}
		else if (s[i] == '\\' && ((q == 0 || (q == '"' && ft_index("\\$\"", s[i + 1]) != -1))))
			ft_memmove(&s[i], &s[i + 1], ft_strlen(s) - i);
	//	if (s[i] == '?')
			// expand
		i++;
	}
	return (s);
}
