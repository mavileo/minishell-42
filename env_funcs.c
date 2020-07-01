/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_funcs.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mavileo <mavileo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/23 19:04:19 by mavileo           #+#    #+#             */
/*   Updated: 2020/06/26 07:24:06 by mavileo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
**	Fonction pour creer des variables d'environnement
**	Le premier maillon de la liste est cree si la liste
**	est nulle, sinon il est ajoute a la fin de celle-ci
**	Ex : t_env *env;
**		 env = add_env(env, "$USER", "username", 1);
**		 env = addadd_env(env, "$PWD", "/home", 1);
*/
int		add_env(char *name, char *value)
{
	t_env	*save;
	t_env	*new;

	save = env;
	if (get_env(name))
	{
		actualise_env(name, value);
		return (0);
	}
	if (!(new = malloc(sizeof(t_env))))
		return (1);
	new->name = ft_strdup(name);
	new->value = ft_strdup(value);
	new->next = NULL;
	if (env == NULL)
	{
		env = new;
		return (0);
	}
	while (env->next != NULL)
		env = env->next;
	env->next = new;
	env = save;
	return (0);
}

int		init_env(void)
{
	char *buff;

	if (!(buff = malloc(sizeof(char) * 501)))
		return (1);
	getcwd(buff, 500);
	add_env("USER", "user42");
	add_env("PWD", buff);
	add_env("PIPESTATUS", "0");
	free(buff);
	return (0);
}

t_env	*get_env(char *name)
{
	t_env *tmp;

	tmp = env;
	if (!name || !tmp)
		return (NULL);
	while (tmp)
	{
		if (!ft_strcmp(tmp->name, name))
			return (tmp);
		tmp = tmp->next;
	}
	return (NULL);
}

char	*get_env_value(char *name)
{
	t_env *tmp;

	tmp = env;
	if (!name || !tmp)
		return (NULL);
	while (tmp)
	{
		if (!ft_strncmp(tmp->name, name, ft_strlen(name)))
			return (tmp->value);
		tmp = tmp->next;
	}
	return (NULL);
}

void	*free_all_env(void)
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