/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commands_list.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mavileo <mavileo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/25 05:34:08 by mavileo           #+#    #+#             */
/*   Updated: 2020/07/25 04:05:58 by mavileo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
**	Prends la liste de token obtenue du parsing, la split en plusieurs
**	listes en fonction des ";".
**	Free la liste passé en paramètre et retourne une liste contenant
**	des listes de tokens.
**
**	On pourra itérer sur cette liste pour executer les commandes.
*/

t_list	*commands_list(t_list *tokens)
{
	t_list *head;
	t_list *commands;
	t_list *nlst;

	if (tokens == NULL)
		return (NULL);
	head = tokens;
	commands = NULL;
	nlst = NULL;
	while (tokens)
	{
		if (((t_token*)tokens->content)->type == SEMICOLON && nlst)
		{
			ft_lstadd_back(&commands, ft_lstnew(nlst));
			nlst = NULL;
		}
		else
			ft_lstadd_back(&nlst, ft_lstnew(ft_token_dup(tokens->content)));
		tokens = tokens->next;
	}
	if (nlst)
		ft_lstadd_back(&commands, ft_lstnew(nlst));
	ft_lstclear(&head, &ft_token_free);
	return (commands);
}

/*
**	Reçoit une liste donc chaque maillon contient une liste de tokens
**	représentant une commande à traiter
**	Itère sur la liste pour executer chaque commande + free
*/

void	execute_commands(t_list *commands)
{
	t_list *head;
	t_list *tmp;

	if (commands == NULL)
		return ;
	head = commands;
	while (commands)
	{
		tmp = commands->content;
		tokens_container(tmp);
		ft_lstclear(&tmp, &ft_token_free);
		commands->content = NULL;
		commands = commands->next;
	}
	ft_lstclear(&head, free);
}
