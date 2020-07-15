/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fds.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mavileo <mavileo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/13 19:41:54 by mavileo           #+#    #+#             */
/*   Updated: 2020/07/15 00:32:21 by mavileo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_fds	*init_fds(void)
{
	t_fds	*fds;

	if (!(fds = malloc(sizeof(t_fds))))
		return (NULL);
 	fds->prev[0] = 0;
	fds->prev[1] = 1;
	fds->actual[0] = 0;
	fds->actual[1] = 1;
	return (fds);
}
