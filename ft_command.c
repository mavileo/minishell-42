/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_command.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mavileo <mavileo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/10 17:29:13 by mavileo           #+#    #+#             */
/*   Updated: 2020/07/10 21:45:49 by mavileo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**env_to_envp(void)
{
	char	**res;
	char	*line;
	t_env	*tmp;
	int		i;

	i = 0;
	tmp = env;
	while (tmp)
	{
		i++;
		tmp = tmp->next;
	}
	if (!(res = malloc(sizeof(char *) * (i + 1))))
		return (NULL);
	tmp = env;
	i = 0;
	while (tmp)
	{
		line = ft_strjoin_free(tmp->name, "=", 0);
		line = ft_strjoin_free(line, tmp->value, 1);
		res[i++] = line;
		tmp = tmp->next;
	}
	res[i] = NULL;
	return (res);
}

int			ft_command(t_list *token)
{
	int		i;
	char	*s;

	i = 0;
	while (builtins[i])
	{
		if (!ft_strcmp(((t_token *)token->content)->args[0], builtins[i]))
			return (g_builtins[i](((t_token *)token->content)->args));
		i++;
	}
	s = ft_strdup(((t_token *)token->content)->args[0]);
	if (get_abs_value(((t_token *)token->content)->args))
	{
		ft_putstr_fd(s, 1);
		ft_putstr_fd(" : commande introuvable\n", 1);
		free(s);
		return (3);
	}
	free(s);
	execve(((t_token *)token->content)->args[0], ((t_token *)token->content)->args, env_to_envp());
	return (2);
}

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
