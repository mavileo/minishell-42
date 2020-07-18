/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_tokens.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/18 16:03:27 by user42            #+#    #+#             */
/*   Updated: 2020/07/18 17:28:50 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
**	Prends une liste chaînée contenant des tokens en paramètre.
**	Retourne le premier maillon devant être traité pour l'exécution.
**
**	Renvoie la première occurence du token ayant la plus haute priorité pour
**	les types SEMICOLON, PIPE, R_x, COMMAND.
**
**	Les types R_x ont tous la même priorité, mais évidemment on peut pas
**	faire un énum qui reespecterai cette règle donc on va devoir le simuler ici.
**
**	Renvoie la dernière occurence du token ayant la plus haute priorité pour
**	les types AND et OR. (à faire, bonus)
*/

static unsigned int	priority(enum e_token_type type)
{
	if (type == R_APPEND || type == R_TRUNC || type == R_INPUT)
		return (1);
	else
		return (type);
}

t_list	*get_first_token(t_list *tokens_list)
{
	t_list	*keep;
	t_token	*token;
	unsigned int current_priority;

	current_priority = 0;
	keep = tokens_list;
	while (tokens_list)
	{
		token = tokens_list->content;
		if (priority(token->type) > current_priority)
		{
			current_priority = priority(token->type);
			keep = tokens_list;
		}
		tokens_list = tokens_list->next;
	}
	return (keep);
}

/*
**	Renvoie le prochain token a executer en se basant sur le token courant
**
**	Si c'est un pipe, renvoie le prochain pipe, ou la prochaine redirection, ou la prochaine commande
**	Si c'est un semicolon, renvoie le prochain semicolon
*/

t_list	*get_next_token(t_list *tokens_list)
{
	t_list	*keep;
	t_token	*token;
	unsigned int current_priority;
	unsigned int max_priority;

	current_priority = 0;
	max_priority = ((t_token*)tokens_list->content)->type;
	tokens_list = tokens_list->next;
	keep = tokens_list;
	while (tokens_list)
	{
		token = tokens_list->content;
		if (priority(token->type) > current_priority
			&& priority(token->type) <= max_priority)
		{
			current_priority = token->type;
			keep = tokens_list;
		}
		if (priority(token->type) == max_priority)
			return (keep);
		tokens_list = tokens_list->next;
	}
	return (keep);
}
