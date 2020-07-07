// 42 HEADER

#include "minishell.h"

/*
**	Prends une liste chaînée contenant des tokens en paramètre.
**	Retourne le premier maillon devant être traité pour l'exécution.
**
**	Renvoie la première occurence du token ayant la plus haute priorité pour
**	les types SEMICOLON, PIPE, R_x, COMMAND.
**
**	Renvoie la dernière occurence du token ayant la plus haute priorité pour
**	les types AND et OR. (à faire, bonus)
*/

t_list	*get_next_token(t_list *tokens_list)
{
	t_list	*keep;
	t_token	*token;
	unsigned int current_priority;

	current_priority = 0;
	keep = tokens_list;
	while (tokens_list)
	{
		token = tokens_list->content;
		if (token->type > current_priority)
		{
			current_priority = token->type;
			keep = tokens_list;
		}
		tokens_list = tokens_list->next;
	}
	return (keep);
}
