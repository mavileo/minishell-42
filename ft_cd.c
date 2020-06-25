/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mavileo <mavileo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/25 01:41:04 by mavileo           #+#    #+#             */
/*   Updated: 2020/06/25 06:59:02 by mavileo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		check_path(char *path)
{
	DIR* dir;

	dir = opendir(path);
	if (dir)
	{
		closedir(dir);
		return (0);
	}
	else
		return (1);
}

int 	ft_cd(char **args)
{
	char *path;

	if (!args[1])
		return (1);
	if (args[1][0] == '/')
		path = args[1];
	else
		path = ft_strjoin_free(get_env_value("PWD"), args[1], 0);
	if (check_path(args[1]))
	{
		if (args[1][0] != '/')
			free(path);
		return (1);
	}
	env = actualise_env("PWD", args[1]);
	if (args[1][0] != '/')
		free(path);
	//actualiser le prompt
	return (0);
}