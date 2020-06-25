/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_funcs2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mavileo <mavileo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/25 04:43:27 by mavileo           #+#    #+#             */
/*   Updated: 2020/06/25 06:45:14 by mavileo          ###   ########.fr       */
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

t_env	*actualise_env(char *name, char *value)
{
	t_env	*ret;
	t_env	*new;
	int		actualise;

	ret = env;
	new = NULL;
	new = add_env(new, name, value);
	if (env && !ft_strncmp(env->name, name, ft_strlen(name)))
	{
		new->next = env->next;
		free(env);
		return (new);
	}
	while (env)
	{
		if (env->next && !ft_strncmp(env->next->name, name, ft_strlen(name)))
		{
			new->next = env->next->next;
			free(env->next);
			env->next = new;
			break;
		}
		env = env->next;
	}
	if (env == NULL)
		free(new);
	return (ret);
}