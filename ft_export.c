/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mavileo <mavileo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/25 04:20:21 by mavileo           #+#    #+#             */
/*   Updated: 2020/07/25 03:36:07 by mavileo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		check_name(char *name)
{
	int j;

	j = 0;
	while (name[j])
	{
		if (!ft_isalnum((int)name[j]) && name[j] != '_')
		{
			ft_putstr_fd("Invalid variable name\n", 1);
			return (1);
		}
		j++;
	}
	return (0);
}

int		ft_export(char **args)
{
	int		i;
	char	*name;
	char	*value;

	i = 0;
	if (!args[1] || !ft_strrchr(args[1], (int)'='))
		return (1);
	while (args[1][i] && args[1][i] != '=')
		i++;
	name = ft_substr(args[1], 0, i);
	if (check_name(name))
	{
		free(name);
		return (1);
	}
	i++;
	value = ft_strdup(args[1] + i);
	add_env(name, value);
	free(name);
	free(value);
	return (0);
}
