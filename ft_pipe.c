/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pipe.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mavileo <mavileo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/14 11:57:19 by mavileo           #+#    #+#             */
/*   Updated: 2020/07/25 04:21:00 by mavileo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		exec_command(t_list *token, t_fds *fds, int status)
{
	(void)status;
	if (!fork())
	{
		close(fds->pipe[0]);
		if (dup2(fds->pipe[1], 1) == -1)
			return (1);
		close(fds->pipe[1]);
		ft_command(token, fds);
		exit(0);
	}
	else
	{
		wait(&status);
		close(fds->pipe[1]);
		if (dup2(fds->save_stdout, 1) == -1)
			return (1);
		if (dup2(fds->save_stdin, 0) == -1)
			return (1);
		if (dup2(fds->pipe[0], 0) == -1)
			return (1);
		close(fds->pipe[0]);
		ft_pipe(token->next->next, fds);
	}
	return (0);
}

int		last_command(t_list *token, t_fds *fds, int status)
{
	char *tmp;

	if (token->next && ((t_token *)token->next->content)->type > 0 &&
		((t_token *)token->next->content)->type < 4)
	{
		g_exec_token[((t_token *)token->next->content)->type](token->next, fds);
		if (dup2(fds->save_stdin, 0) == -1)
			return (1);
		return (0);
	}
	if (ft_command(token, fds) == -1)
	{
		wait(&status);
		add_env("PIPESTATUS", (tmp = ft_itoa(WEXITSTATUS(status))));
		free(tmp);
	}
	wait(&status);
	if (dup2(fds->save_stdin, 0) == -1)
		return (1);
	return (0);
}

int		ft_pipe(t_list *token, t_fds *fds)
{
	static int	count = 0;
	int			status;

	status = 0;
	if (!count)
		token = token->prev;
	if (!count || (token->next && token->next->next &&
		((t_token *)token->next->content)->type == PIPE &&
		((t_token *)token->next->next->content)->type == COMMAND))
	{
		count++;
		if (pipe(fds->pipe) == -1)
			return (1);
		if (exec_command(token, fds, status))
			return (1);
	}
	else
	{
		count = 0;
		return (last_command(token, fds, status));
	}
	return (0);
}
