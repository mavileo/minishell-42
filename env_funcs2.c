/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_funcs2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mavileo <mavileo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/25 04:43:27 by mavileo           #+#    #+#             */
/*   Updated: 2020/07/25 05:08:31 by mavileo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*add_env_to_str(char *str, char *res, int i)
{
	char	*to_free;
	int		len;

	len = 0;
	i++;
	if (str[i] == '?')
	{
		res = ft_strjoin_free(res, get_env_value("PIPESTATUS"), 1);
		return (res);
	}
	while (str[i + len] && ft_isalnum(str[i + len]))
		len++;
	to_free = ft_substr(str, i, len);
	res = ft_strjoin_free(res, get_env_value(to_free), 1);
	free(to_free);
	to_free = NULL;
	return (res);
}

char	*replace_env_in_str(char *str)
{
	char	*res;
	int		i;

	i = 0;
	res = ft_strdup("");
	if (!ft_strrchr(str, (int)'$'))
		return (str);
	while (str[i])
	{
		if (str[i] != '$')
			res = ft_strjoin_free(res, ft_substr(str + i, 0, 1), 3);
		else
		{
			res = add_env_to_str(str, res, i);
			i++;
			while (str[i] && ft_isalnum(str[i]))
				i++;
			if (!(str[i] == '?' && str[i - 1] == '$'))
				i--;
		}
		i++;
	}
	return (res);
}

void	*free_env(t_env *g_env)
{
	free(g_env->name);
	free(g_env->value);
	free(g_env);
	g_env = NULL;
	return (g_env);
}

t_env	*init_actualise(char *name, char *value)
{
	t_env *new;

	if (!(new = malloc(sizeof(t_env))))
		return (new);
	new->name = ft_strdup(name);
	new->value = ft_strdup(value);
	if (g_env && !ft_strncmp(g_env->name, name, ft_strlen(name)))
	{
		new->next = g_env->next;
		free_env(g_env);
		g_env = new;
		return (NULL);
	}
	return (new);
}

int		actualise_env(char *name, char *value)
{
	t_env	*ret;
	t_env	*new;

	ret = g_env;
	if (!(new = init_actualise(name, value)))
		return (0);
	while (g_env)
	{
		if (g_env->next && !ft_strncmp(g_env->next->name, name,
			ft_strlen(name)))
		{
			new->next = g_env->next->next;
			free_env(g_env->next);
			g_env->next = new;
			break ;
		}
		g_env = g_env->next;
	}
	if (g_env == NULL)
		free_env(new);
	g_env = ret;
	return (0);
}
