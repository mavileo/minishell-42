/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens_container.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mavileo <mavileo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/13 01:34:55 by mavileo           #+#    #+#             */
/*   Updated: 2020/07/20 08:01:27 by mavileo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		tokens_container(t_list *tokens_list)
{
	t_list	*token;
	t_fds	*fds;
	int		status;
	char	*tmp;

	fds = init_fds();
	if (!(token = get_first_token(tokens_list)))
		return (0);
	g_exec_token[((t_token *)token->content)->type](token, fds);
	status = 0;
	wait(&status);
	add_env("PIPESTATUS", (tmp = ft_itoa(WEXITSTATUS(status))));
	free(tmp);
	close(fds->save_stdin);
	close(fds->save_stdout);
	free(fds);
	return (0);
}
