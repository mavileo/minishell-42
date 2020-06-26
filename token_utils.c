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

void	ft_token_free(t_token *token)
{
	ft_tabfree((void**)token->args);
	free(token);
	token = NULL;
}

void		ft_print_token_list(t_list *l) // TEST ONLY !!! USELESS
{
	static const char *strs[] = {"COMMAND", "REDIR1", "REDIR2", "REDIR3", "PIPE", "SEMICOLON"};
	int i = 0;
	t_token *token;

	while (l)
	{
		token = l->content;
		printf("{ type: %s, args: [", strs[token->type]);
		while (token->args && token->args[i])
		{
			printf("\"%s\", ", token->args[i] ? token->args[i] : "null");
			i++;
		}
		printf("]}\n");
		l = l->next;
	}
}
