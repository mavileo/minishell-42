/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_funcs2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mavileo <mavileo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/25 04:43:27 by mavileo           #+#    #+#             */
/*   Updated: 2020/06/26 07:25:02 by mavileo          ###   ########.fr       */
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
	res = ft_strjoin_free(res, get_env_value((to_free =
	ft_substr(str, i, len))), 1);
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

void	*free_env(t_env *env)
{
	free(env->name);
	free(env->value);
	free(env);
	env = NULL;
	return (env);
}

t_env	*init_actualise(char *name, char *value)
{
	t_env *new;

	if (!(new = malloc(sizeof(t_env))))
		return (new);
	new->name = name;
	new->value = value;
	if (env && !ft_strncmp(env->name, name, ft_strlen(name)))
	{
		new->next = env->next;
		free_env(env);
		env = new;
		return (NULL);
	}
	return (new);
}

int		actualise_env(char *name, char *value)
{
	t_env	*ret;
	t_env	*new;
//	int		actualise;

	ret = env;
	if (!(new = init_actualise(name, value)))
		return (0);
	while (env)
	{
		if (env->next && !ft_strncmp(env->next->name, name, ft_strlen(name)))
		{
			new->next = env->next->next;
			free_env(env->next);
			env->next = new;
			break;
		}
		env = env->next;
	}
	if (env == NULL)
		free_env(new);
	env = ret;
	return (0);
}
