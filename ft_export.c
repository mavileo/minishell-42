/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mavileo <mavileo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/25 04:20:21 by mavileo           #+#    #+#             */
/*   Updated: 2020/06/27 04:24:01 by mavileo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int 	ft_export(char **args)
{
	int		i;
	char	*name;
	char	*value;

	i = 0;
	if (!args[1])
		return (1);
	while (args[1][i] && args[1][i] != '=')
		i++;
	name = ft_substr(args[1], 0, i);
	i++;
	value = ft_strdup(args[1] + i);
	add_env(name, value);
	free(name);
	free(value);
	return (0);
}
