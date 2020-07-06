/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mavileo <mavileo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/25 01:41:04 by mavileo           #+#    #+#             */
/*   Updated: 2020/07/06 17:07:17 by mavileo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		check_path(char *path, int print)
{
	DIR* dir;

	dir = opendir(path);
	if (dir)
	{
		closedir(dir);
		return (0);
	}
	if (print)
		ft_putstr_fd("Invalid path\n", 1);
	return (1);
}

char	*check_points(char *p, int i, int count)
{
	char *tmp;

	tmp = p;
	if (p[i] == '.' && p[i - 1] == '/' && (p[i + 1] == '/' || !p[i + 1]))
	{
		p = ft_strjoin_free(ft_substr(p, 0, i - 1),
		ft_substr(p, i+ 1, ft_strlen(p)), 3);
		free(tmp);
	}
	else if (p[i] == '.' && p[i - 1] == '/' && p[i + 1] &&
	p[i + 1] == '.' && (p[i + 2] == '/' || !p[i + 2]))
	{
		count = i;
		while (count && p[count] != '/')
			count--;
		count--;
		while (count > 0 && p[count] != '/')
			count--;
		p = ft_strjoin_free(count > 0 ? ft_substr(p, 0, count) :
		ft_strdup(""), i + 2 >= ft_strlen(p) ? ft_strdup("") :
		ft_substr(p, i + 2, ft_strlen(p)), 3);
		free(tmp);
	}
	return (p);
}

char	*get_absolute(char *s)
{
	if (s[0] == '/')
		return (ft_strdup(s));
	else
		return (ft_strjoin_free(ft_strjoin_free(get_env_value("PWD"),
		"/", 0), s, 1));
}

char	*get_path(char *s)
{
	char	*path;
	char	*tmp;
	int		i;
	int		count;

	i = 0;
	path = get_absolute(s);
	tmp = path;
	while (path[i])
	{
		if ((path = check_points(path, i, count)) != tmp && !(i = 0))
			tmp = path;
		else
			i++;
	}
	if (!path || !path[0])
	{
		free(path);
		path = ft_strdup("/");
	}
	if (ft_strlen(path) > 1 && path[ft_strlen(path) - 1] == '/')
		path[ft_strlen(path) - 1] = 0;
	return (path);
}

int 	ft_cd(char **args)
{
	char *path;
	char *pwd;

	if (!args[1])
		return (1);
	path = get_path(args[1]);
	if (check_path(path, 1))
	{
		free(path);
		return (1);
	}
	actualise_env("PWD", path);
	//actualiser le prompt
	return (0);
}
