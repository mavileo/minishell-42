// 42 HEADER

#include "minishell.h"

t_token	*ft_token_new(enum e_token_type type, char **args)
{
	t_token	*token;

	if ((token = malloc(sizeof(t_token))) == NULL)
		return (NULL);
	token->type = type;
	token->args = args;
	return (token);
}

void	ft_token_free(void *token)
{
	t_token *t;

	t = (t_token *)token;
	if (t)
	{
		ft_tabfree(t->args);
		free(t);
		t = NULL;
	}
}

t_token	*ft_token_dup(t_token *src)
{
	t_token	*token;

	if ((token = malloc(sizeof(t_token))) == NULL)
		return (NULL);
	token->type = src->type;
	token->args = (char**)ft_tabdup(src->args, (void*)ft_strdup);
	return (token);
}


void		ft_print_token_list(t_list *l) // TEST ONLY !!! USELESS
{
	static const char *strs[] = {"COMMAND", "R_APPEND", "R_TRUNC", "R_IN", "PIPE", "SEMICOLON"};
	int i;
	t_token *token;

	if (!l)
		write(1, "list null\n", 10);
	while (l)
	{
		token = l->content;
		printf("{ type: %10s, args: [", strs[token->type]);
		i = 0;
		while (token->args && token->args[i])
		{
			printf("\"%s\", ", token->args[i] ? token->args[i] : "null");
			i++;
		}
		printf("null] }\n");
		l = l->next;
	}
}
