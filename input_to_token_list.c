// 42 HEADER

#include "minishell.h"

static void		quotes_onoff(char *q, char c)
{
	if ((c == 39 || c == '"') && *q == 0)
		*q = c;
	else if ((c == 39 && *q == 39) || (c == '"' && *q == '"'))
		*q = 0;
}

static t_list	*ft_split1(char *s) // split aux espaces en faisant attention aux quotes
{
	char q;
	t_list *l;
	unsigned int i;
	unsigned int j;

	l = NULL;
	i = 0;
	q = 0;
	while (s[i])
	{
		while (s[i] != '\0' && s[i] == 32 && q == 0)
			i++;
		j = i;
		while (s[i] != '\0' && (s[i] != 32 || (s[i] == 32 && q != 0)))
		{
			quotes_onoff(&q, s[i]);	
			i++;
		}
		if ((s[i] == 32 && q == 0) || (s[i] == '\0' && s[i - 1] != 32))
			ft_lstadd_back(&l, ft_lstnew(ft_substr(s, j, (i - j))));
	}
	if (q != 0)
	{
		printf("syntax error: open quotes %d\n", q);
		ft_lstclear(&l, free);
	}
	return (l);
}

static const char *g_symbols_strs[6] = {
	">>",
	">",
	"<",
	"|",
	";",
	NULL
};

static int		there_is_an_operator(const char *s, unsigned int *i, unsigned int *j) // renvoie les index start et end d'une substring représentant un operateur
{
	char q;
	unsigned int x;

	q = 0;
	*i = -1;
	while (s[++(*i)])
	{
		quotes_onoff(&q, s[*i]);
		if (q == 0 && ft_index(CMP_SYMBOLS, s[*i]) != -1)
		{
			x = -1;
			while (g_symbols_strs[++x])
			{
				*j = ft_strlen(g_symbols_strs[x]);
				if (ft_strncmp(&s[*i], g_symbols_strs[x], *j) == 0)
				{
					*j = *i + *j;
					return (1);
				}
			}
		}
	}
	return (0);
}

static void	ft_split2(t_list **l) // cherche les operateurs et resplit
{
	unsigned int i;
	unsigned int j;
	char *s;
	t_list *current;

	current = *l;
	while (current && (s = current->content))
	{
		if (there_is_an_operator(s, &i, &j))
		{
			if (i != 0)
			{
				ft_lstinsert(current, ft_lstnew(ft_substr(s, i, (j - i)))); // new = op
				if (s[j] != 0)
					ft_lstinsert(current->next, ft_lstnew(ft_substr(s, j, ft_strlen(s)))); // new = after
				s[i] = 0; // cut à l'opérateur
			}
			else if (s[j] != 0)
			{
				ft_lstinsert(current, ft_lstnew(ft_substr(s, j, ft_strlen(s)))); // new = after
				s[j] = 0; // cut à l'opérateur
			}
		}
		current = current->next;
	}
}

static t_list	*to_tokens(t_list **l)
{
	// regarde tout les maillons, tant que c'est du word on concat en 2darray, si c'est un operateur on garde le maillon, ainsi de suite
	// sauf redirection : premier word apres operateur redirection == argument de redirection à mettre dans son token et words suivant == arguments de la commande
	*l = ft_lstnew(ft_token_new(COMMAND, NULL));
	return (NULL);
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

	l = ft_split1(input);
	ft_lstprint(l, (void*)ft_putstr);
	ft_split2(&l);
	ft_lstprint(l, (void*)ft_putstr);

	to_tokens(&l);
	ft_print_token_list(l);

	ft_lstclear(&l, (void*)ft_token_free);
	return (NULL);
}
