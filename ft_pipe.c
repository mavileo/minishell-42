/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pipe.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mavileo <mavileo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/14 11:57:19 by mavileo           #+#    #+#             */
/*   Updated: 2020/07/18 02:58:45 by mavileo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		ft_pipe(t_list *token, t_fds *fds)
{
	static int count = 0;
	int status;

	if (!count)
		token = token->prev;
	if (!count || (token->next && ((t_token *)token->next->content)->type == PIPE))
	{
		count++;
		if (!(fork()))
		{
			if (pipe(fds->pipe) == -1)
				return (1);
			if (!fork())
			{
				close(fds->pipe[0]);
				if (dup2(fds->pipe[1], 1) == -1)
					return (1);
				close(fds->pipe[1]);
				ft_command(token, fds);
			}
			else
			{
				close(fds->pipe[1]);
				if (dup2(fds->save_stdout, 1) == -1)
					return (1);
				if (dup2(fds->save_stdin, 0) == -1)
					return (1);
				if (dup2(fds->pipe[0], 0) == -1)
					return (1);
				close(fds->pipe[0]);
				if (!fork())
					ft_pipe(token->next->next, fds);
				else
					wait(&status);
			}
		}
		else
			wait(&status);
	}
	else
	{
		if (!fork())
			ft_command(token, fds);
		else
			wait(&status);
	}
	exit(0);
	return (0);
}
