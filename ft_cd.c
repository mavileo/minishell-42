/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mavileo <mavileo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/25 01:41:04 by mavileo           #+#    #+#             */
/*   Updated: 2020/07/25 01:33:40 by user42           ###   ########.fr       */
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
		ft_strdup(""), i + 2 >= (int)ft_strlen(p) ? ft_strdup("") :
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
	count = 0;
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
/*
int 	ft_cd(char **args)
{
	char *path;

	if (!args[1])
	{
		path = replace_env_in_str("/home/$USER");
		actualise_env("PWD", path);
		chdir((const char *)path);
		free(path);
		return (0);
	}
	path = get_path(args[1]);
	if (check_path(path, 1))
	{
		free(path);
		return (1);
	}
	actualise_env("PWD", path);
	chdir((const char *)path);
	free(path);
	return (0);
}
*/

int 	ft_cd(char **args)
{
	char *path;
	char *cwd;
	int r;

	path = args[1] ? ft_strdup(args[1]) : replace_env_in_str("/home/$USER");
	r = 1;
	if (chdir((const char *)path) == 0) // soit ça marche d'un coup
		r = 0;
	else // soit on essaie en construisant le path
	{
		cwd = getcwd(NULL, 0);
		cwd = ft_strjoin_free(cwd, "/", 1);
		path = ft_strjoin_free(cwd, path, 3);
		if (chdir((const char *)path) == 0)
			r = 0;
	}
	if (r == 1) // soit c'était invalide et on imprime l'erreur et renvoie 1
		ft_dsplerr(args[1], strerror(errno));	
	else
		actualise_env("PWD", path);
	free(path);
	return (r);
}

