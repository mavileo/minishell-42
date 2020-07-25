/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mavileo <mavileo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/06 16:55:21 by mavileo           #+#    #+#             */
/*   Updated: 2020/07/25 03:54:13 by mavileo          ###   ########.fr       */
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

static char		**get_path_tab(char *path)
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

/*
**	Prends un deux bout de path/repertoire
**	Les assemblent avec un '/' entre les deux
**
**	"/bin" + "/" + "cat"
*/

char			*build_path(char *s1, char *s2)
{
	char *built_path;

	built_path = NULL;
	built_path = ft_strjoin_free(s1, "/", 0);
	built_path = ft_strjoin_free(built_path, s2, 1);
	return (built_path);
}

static char		*get_exe_path(char **paths, char *name)
{
	struct stat	sb;
	char		*file;
	int			i;

	i = 0;
	while (paths[i])
	{
		if (paths[i][ft_strlen(paths[i]) - 1] != '/')
			file = build_path(paths[i], name);
		else
			file = ft_strjoin_free(paths[i], name, 0);
		if (stat(file, &sb) == 0 && (sb.st_mode & S_IFMT) != S_IFDIR)
			return (file);
		else
		{
			free(file);
			i++;
		}
	}
	return (NULL);
}

char			*get_abs_value(char *cmd)
{
	char		*built_path;
	char		**path_tab;
	struct stat	sb;

	if (!get_env_value("PATH"))
		return (NULL);
	if ((cmd[0] == '/') && (stat(cmd, &sb) == 0 &&
		(sb.st_mode & S_IFMT) != S_IFDIR))
		return (ft_strdup(cmd));
	if (cmd[0] != '/' && ft_index(cmd, '/') > 0)
	{
		built_path = getcwd(NULL, 0);
		built_path = ft_reassign(built_path, build_path(built_path, cmd));
		if (stat(cmd, &sb) == 0 && (sb.st_mode & S_IFMT) != S_IFDIR)
			return (built_path);
		free(built_path);
	}
	else
	{
		path_tab = get_path_tab(get_env_value("PATH"));
		built_path = get_exe_path(path_tab, cmd);
		ft_tabfree(path_tab);
		return (built_path);
	}
	return (NULL);
}
