/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mavileo <mavileo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/06 16:55:21 by mavileo           #+#    #+#             */
/*   Updated: 2020/07/10 17:51:02 by mavileo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int		get_nb_paths(char *path)
{
	char	*tmp;
	int		i;
	int		nb_path;
	int		prev;

	prev = 0;
	nb_path = 0;
	i = 0;
	while ((!i || path[i - 1]) && path[i])
	{
		prev = i;
		while (path[i] && path[i] != ':')
			i++;
		tmp = ft_substr(path, prev, i - prev);
		if (!check_path(tmp, 0))
			nb_path++;
		free(tmp);
		tmp = NULL;
		i++;
	}
	return (nb_path);
}

static char	**get_path_tab(char *path)
{
	char	*tmp;
	int		i;
	int		nb_path;
	int		prev;
	char	**tab;

	prev = 0;
	nb_path = 0;
	i = 0;
	if (!(tab = malloc(sizeof(char *) * (get_nb_paths(path) + 1))))
		return (NULL);
	while ((!i || path[i - 1]) && path[i])
	{
		prev = i;
		while (path[i] && path[i] != ':')
			i++;
		tmp = ft_substr(path, prev, i - prev);
		if (!check_path(tmp, 0))
			tab[nb_path++] = tmp;
		else
			free(tmp);
		i++;
	}
	tab[nb_path] = NULL;
	return (tab);
}

static char	*get_exe_path(char **paths, char *name)
{
	struct	stat sb;
	char	*file;
	int		i;

	i = 0;
	while (paths[i])
	{
		if (paths[i][ft_strlen(paths[i]) - 1] != '/')
		{
			file = ft_strjoin_free(paths[i], "/", 0);
			file = ft_strjoin_free(file, name, 1);
		}
		else
			file = ft_strjoin_free(paths[i], name, 0);
		if (stat(file, &sb) == 0 && sb.st_mode & S_IXUSR)
			return (file);
		else
		{
			free(file);
			i++;
		}
	}
	return (NULL);
}

int		get_abs_value(char **args)
{
	char 	**paths;
	struct	stat sb;
	
	if (!args[0] || !*args[0])
		return (1);
	if (stat(args[0], &sb) == 0 && sb.st_mode & S_IXUSR)
		return (0);
	paths = get_path_tab(get_env_value("PATH"));
	args[0] = ft_reassign(args[0], get_exe_path(paths, args[0]));
	ft_tabfree(paths); // JUST ADDED
	return (args[0] == NULL);
}
