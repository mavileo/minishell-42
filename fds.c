/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fds.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mavileo <mavileo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/13 19:41:54 by mavileo           #+#    #+#             */
/*   Updated: 2020/07/18 00:24:19 by mavileo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_fds	*init_fds(void)
{
	t_fds	*fds;

	if (!(fds = malloc(sizeof(t_fds))))
		return (NULL);
	fds->save_stdin = dup(0);
	fds->save_stdout = dup(1);
	fds->pipe[0] = 0;
	fds->pipe[1] = 1;
	return (fds);
}
