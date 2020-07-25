/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mavileo <mavileo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/25 07:06:11 by mavileo           #+#    #+#             */
/*   Updated: 2020/07/25 04:07:22 by mavileo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		ft_unset(char **args)
{
	t_env	*save;
	t_env	*prev;
	int		i;

	i = 1;
	save = env;
	while (args[i++] && !(prev = NULL))
	{
		env = save;
		while (env)
		{
			if (!ft_strcmp(env->name, args[i - 1]))
			{
				if (prev)
					prev->next = env->next;
				else
					save = env->next;
				free_env(env);
				break ;
			}
			prev = env;
			env = env->next;
		}
	}
	return (!(env = save));
}
