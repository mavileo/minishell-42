/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mavileo <mavileo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/25 04:52:09 by mavileo           #+#    #+#             */
/*   Updated: 2020/07/25 04:52:33 by mavileo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
