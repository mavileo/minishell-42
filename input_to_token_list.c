// 42 HEADER

#include "minishell.h"

static t_list	*ft_split_iq(char *s)
{
	char q;
	t_list *l;
	unsigned int i;
	unsigned int j;

	l = NULL;
	i = 0;
	j = 0;
	q = 0;
	while (s[i])
	{
		while (s[i] != '\0' && s[i] == 32 && q == 0)
			i++;
		j = i;
		while (s[i] != '\0' && (s[i] != 32 || (s[i] == 32 && q != 0)))
		{
			if ((s[i] == 39 || s[i] == '"') && q == 0)
				q = s[i];
			else if ((s[i] == 39 && q == 39) || (s[i] == '"' && q == '"'))
				q = 0;
			i++;
		}
		if ((s[i] == 32 && q == 0) || (s[i] == '\0' && s[i - 1] != 32))
			ft_lstadd_back(&l, ft_lstnew(ft_substr(s, j, (i - j))));
	}
	if (q != 0)
	{
		write(1, "syntax error: open quotes\n", ft_strlen("syntax error: open quotes\n"));
		ft_lstclear(&l, free);
	}
	return (l);
}

/*
**	Récupère la string input, la transforme en une liste de tokens.
**	exemple :
**	
** "cat space.txt | grep 'aliens' >> earth.txt"
**	
**		COMMAND       ->    PIPE   ->    COMMAND        ->   REDIR2     -> NULL
** ['cat', 'space.txt']      []     ['grep', 'aliens']    ['earth.txt']
**	
**
**	Règles d'interprétation BASH :
**
**	single quotes = pas d'expand
**	double quotes = expand, les singles quotes sont de simples chars, les espaces aussi
**	rien = expand
**	escapes : quotes, escape char
**  un operateur entres quotes n'est pas un opérateur ('>' != >)
**
**
**	Un quote non fermé entraîne une syntax error
**	Un opérateur après un autre entraîne une syntax error
**
*/

t_token     *input_to_token_list(char *input, void *env)
{
	(void)env;
	t_list	*l;
//	char **words;
//	unsigned int i;

	l = ft_split_iq(input);
	ft_lstprint(l, (void*)ft_putstr);
	ft_lstclear(&l, free);

	return (NULL);
}
