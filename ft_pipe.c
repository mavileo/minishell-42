/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pipe.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mavileo <mavileo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/14 11:57:19 by mavileo           #+#    #+#             */
/*   Updated: 2020/07/15 17:07:30 by mavileo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
int		ft_pipe(t_list *token, t_fds *fds)
{
	int pid;
	int pid2;
	int status;

	//if (token->next && token->next->next && token->next->next->type = PIPE)
	if (!(pid2 = fork()))
	{
		if (pipe(fds->actual) == -1)
			return (1);
		if (!(pid = fork()))
		{
			close(fds->actual[0]);
			if (dup2(fds->actual[1], 1) == -1)
				return (1);
			close(fds->actual[1]);
			ft_command(token->prev, fds);
		}
		else
		{
			//fds->prev[0] = fds->actual[0];
			//fds->prev[1] = fds->actual[1];
			//if (pipe(fds->actual) == -1)
			//	return (1);
			close(fds->actual[1]);
			if (dup2(fds->actual[0], 0) == -1)
				return (1);
			close(fds->actual[0]);
			ft_command(token->next, fds);
		}
	}
	else
		waitpid(pid2, &status, 0);
	return (0);
}
