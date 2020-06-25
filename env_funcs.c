/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_funcs.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mavileo <mavileo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/23 19:04:19 by mavileo           #+#    #+#             */
/*   Updated: 2020/06/25 06:27:52 by mavileo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
**	Fonction pour creer des variables d'environnement
**	Le premier maillon de la liste est cree si la liste
**	est nulle, sinon il est ajoute a la fin de celle-ci
**	Ex : t_env *env;
**		 env = add_env(env, "$USER", "username");
**		 env = addadd_env(env, "$PWD", "/home");
*/
t_env	*add_env(t_env *env, char *name, char *value)
{
	t_env	*save;
	t_env	*new;

	save = env;
	if (!(new = malloc(sizeof(t_env))))
		return (NULL);
	new->name = ft_strdup(name);
	new->value = ft_strdup(value);
	new->next = NULL;
	if (env == NULL)
		return (new);
	while (env->next != NULL)
		env = env->next;
	env->next = new;
	return (save);
}

int		init_env(void)
{
	char *buff;

	if (!(buff = malloc(sizeof(char) * 501)))
		return (1);
	getcwd(buff, 500);
	env = add_env(env, "USER", "user42");
	env = add_env(env, "PWD", buff);
	env = add_env(env, "PIPESTATUS", "0");
	free(buff);
	return (0);
}

t_env	*get_env(char *name)
{
	while (env)
	{
		if (!ft_strncmp(env->name, name, ft_strlen(name)))
			return (env);
		env = env->next;
	}
	return (NULL);
}

char	*get_env_value(char *name)
{
	while (env)
	{
		if (!ft_strncmp(env->name, name, ft_strlen(name)))
			return (env->value);
		env = env->next;
	}
	return (NULL);
}

void	*free_env(void)
{
	t_env	*tmp;

	while (env)
	{
		free(env->name);
		free(env->value);
		tmp = env->next;
		free(env);
		env = tmp;
	}
	return (env);
}