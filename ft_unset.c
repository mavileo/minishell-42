/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mavileo <mavileo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/25 07:06:11 by mavileo           #+#    #+#             */
/*   Updated: 2020/07/25 05:05:50 by mavileo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		ft_unset(char **args)
{
	t_env	*save;
	t_env	*prev;
	int		i;

	i = 1;
	save = g_env;
	while (args[i++] && !(prev = NULL))
	{
		g_env = save;
		while (g_env)
		{
			if (!ft_strcmp(g_env->name, args[i - 1]))
			{
				if (prev)
					prev->next = g_env->next;
				else
					save = g_env->next;
				free_env(g_env);
				break ;
			}
			prev = g_env;
			g_env = g_env->next;
		}
	}
	return (!(g_env = save));
}
