/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_token_functions.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/24 16:31:34 by user42            #+#    #+#             */
/*   Updated: 2020/07/24 16:31:36 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
**	Ajoute un maillon du type commande a la liste token_list
**
**	Si une commande est déjà en cours de construction, alors on traite le
**	content comme un arg et on l'ajoute au maillon déjà alloué
**	Sinon on créer effectivement un nouveau maillon	
**
**	Renvoie le token du mailon ajouté, ou NULL si pbm
*/

t_token	*add_command_token(t_list **token_lst, t_list **e, t_token **current)
{
	t_token *new_t;
	t_list	*new_e;
	char *str;

	if (current && *current)
	{
		new_t = *current;
		str = escape_expand((*e)->content);
		new_t->args = ft_tabpush(new_t->args, str);
		free(str);
		return (*current);
	}
	str = escape_expand((*e)->content);
	new_t = ft_token_new(COMMAND, ft_tabpush(NULL, str));
	free(str);
	new_e = ft_lstnew(new_t);
	ft_lstadd_back(token_lst, new_e);
	*current = new_t;
	return (new_t);
}

/*
**	Le ';' sépare les commandes, donc cette fonction nullify le pointeur qui
**	contient le token représantant la commande en cours de construction.
**	Si le maillon précédent est de type opérateur (donc pas du type COMMAND)
**	renvoie null et print l'erreur
*/

t_token	*add_semicolon_token(t_list **token_lst, t_list **e, t_token **current)
{
	(void)e;
	t_list *new;
	t_token *token;
	t_token	*last_token;

	*current = NULL;
	new = ft_lstlast(*token_lst);
	last_token = new ? new->content : NULL;
	if (last_token == NULL || last_token->type > R_INPUT)
	{
		printf("syntax error near token ';'\n");
		return (NULL);
	}
	token = ft_token_new(SEMICOLON, NULL);
	new = ft_lstnew(token);
	ft_lstadd_back(token_lst, new);
	return (token);
}

/*
**	Le '|' sépare les commandes, donc cette fonction nullify le pointeur qui
**	contient le token représantant la commande en cours de construction.
**	Si le maillon précédent est de type opérateur (donc pas du type COMMAND)
**	renvoie null et print l'erreur
**	Si l'élement suivant dans la liste à transformer est NULL, syntax error
*/

t_token	*add_pipe_token(t_list **token_lst, t_list **e, t_token **current)
{
	t_list *new;
	t_token *token;
	t_token	*last_token;

	*current = NULL;
	new = ft_lstlast(*token_lst);
	last_token = new ? new->content : NULL;
	if (last_token == NULL || last_token->type > R_INPUT || (*e)->next == NULL)
	{
		printf("syntax error near token '|'\n");
		return (NULL);
	}
	token = ft_token_new(PIPE, NULL);
	new = ft_lstnew(token);
	ft_lstadd_back(token_lst, new);
	return (token);
}

/*
**	Les redirections ne séparent pas les commandes, elle prennent le premier
**	element qui les suivent comme argument.
**
**	A part le premier element suivant la redirection, tout element se trouvant
**	avant ou après est considéré comme la commande et ses arguments
**
**	Si l'élement suivant dans la liste à transformer est NULL, syntax error
*/

t_token	*add_redirection_token(t_list **token_lst, t_list **e, t_token **current)
{
	(void)current;
	t_token *token;
	unsigned int type;
	char *str;

	token = NULL;
	if ((*e)->next == NULL || ft_tabindex(g_symbols_strs, (*e)->next->content) + 1 != COMMAND)
		printf("syntax error near token %s\n", (char*)(*e)->content);
	else
	{
		if ((*e)->prev == NULL && (*e)->next && (*e)->next->next)
		{
			*current = ft_token_new(COMMAND, NULL);
			ft_lstadd_back(token_lst, ft_lstnew(*current));
		}
		type = ft_tabindex(g_symbols_strs, (*e)->content) + 1;
		str = escape_expand((*e)->next->content);
		token = ft_token_new(type, ft_tabpush(NULL, str));
		free(str);
		ft_lstadd_back(token_lst, ft_lstnew(token));
		*e = (*e)->next;
	}
	return (token);
}
