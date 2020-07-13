/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mavileo <mavileo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/27 04:29:14 by mavileo           #+#    #+#             */
/*   Updated: 2020/07/13 12:16:27 by mavileo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		ft_exit(char **args)
{
	(void)args;
	free_all_env();
	// free tout les elements mallocs
	ft_putstr_fd("exit\n", 1);
	exit(0);
}
