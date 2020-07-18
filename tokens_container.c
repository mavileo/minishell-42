/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens_container.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mavileo <mavileo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/13 01:34:55 by mavileo           #+#    #+#             */
/*   Updated: 2020/07/18 02:45:06 by mavileo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		tokens_container(t_list *tokens_list)
{
	t_list	*token;
	t_fds	*fds;
	int		status;

	fds = init_fds();
	if (!(token = get_next_token(tokens_list)))
		return (0);
	if (!(fork()))
		g_exec_token[((t_token *)token->content)->type](token, fds);
	else
		wait(&status);
	close(fds->save_stdin);
	close(fds->save_stdout);
	free(fds);
	return (0);
}
