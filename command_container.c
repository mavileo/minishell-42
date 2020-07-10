/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_container.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mavileo <mavileo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/10 17:17:16 by mavileo           #+#    #+#             */
/*   Updated: 2020/07/10 21:39:57 by mavileo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// todo: typedef sur ce type de pointeurs
// tableau de pointeurs sur fonctions qui contient toutes les fonctions associé
// à chaques tokens

int		command_container(t_list *tokens_list)
{
	t_list *token;
	int ret;
	int status;
	int pid;

	token = get_next_token(tokens_list);
	if (!(pid = fork()))
		ret = g_exec_token[((t_token *)token->content)->type](token);
	else
		waitpid(pid, &status, 0);
	if (ret != 2)
	{
		if (ret < 2)
			return (ret);
		else
			return (1);
	}
	return (WEXITSTATUS(status));
}
