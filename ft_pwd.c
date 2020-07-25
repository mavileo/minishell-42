/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mavileo <mavileo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/23 18:51:00 by mavileo           #+#    #+#             */
/*   Updated: 2020/07/25 03:35:56 by mavileo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		ft_pwd(char **args)
{
	char *path;

	(void)args;
	path = getcwd(NULL, 0);
	if (path == NULL)
		return (1);
	ft_putendl_fd(path, 1);
	free(path);
	return (0);
}
