/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mavileo <mavileo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/23 18:51:00 by mavileo           #+#    #+#             */
/*   Updated: 2020/07/13 12:16:57 by mavileo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int 	ft_pwd(char **args)
{
	char *path;

	(void)args;
	path = get_env_value("PWD");
	if (path == NULL)
		return (1);
	ft_putstr_fd(path, 1);
	ft_putstr_fd("\n", 1);
	return (0);
}
