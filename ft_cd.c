/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mavileo <mavileo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/25 01:41:04 by mavileo           #+#    #+#             */
/*   Updated: 2020/06/26 05:42:34 by mavileo          ###   ########.fr       */
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
	ft_putstr_fd("Invalid path\n", 1);
	return (1);
}

int		check_points(char *path)
{
	char	*new;
	int		i;

	if (!ft_strcmp(".", path))
		return (1);
	if (!ft_strcmp("..", path))
	{
		new = get_env_value("PWD");
		if (!ft_strcmp("/", new))
			return (1);
		i = ft_strlen(new) - 1;
		while (new[i] != '/')
			i--;
		new = ft_substr(new, 0, i);
		actualise_env("PWD", new);
		free(new);
		return (1);
	}
	return (0);
}

int 	ft_cd(char **args)
{
	char *path;
	char *pwd;

	if (!args[1])
		return (1);
	if (check_points(args[1]))
		return (0);
	if (args[1][0] == '/')
		path = args[1];
	else
	{
		pwd = ft_strjoin_free(get_env_value("PWD"), "/", 0);
		path = ft_strjoin_free(pwd, args[1], 1);
	}
	if (check_path(path))
	{
		if (args[1][0] != '/')
			free(path);
		return (1);
	}
	actualise_env("PWD", path);
	if (args[1][0] != '/')
		free(path);
	//actualiser le prompt
	return (0);
}