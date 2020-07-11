/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_command.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mavileo <mavileo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/10 17:29:13 by mavileo           #+#    #+#             */
/*   Updated: 2020/07/11 17:27:27 by mavileo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int builtin;

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
	char	*s;

	s = ft_strdup(((t_token *)token->content)->args[0]);
	if (get_abs_value(((t_token *)token->content)->args))
	{
		ft_putstr_fd(s, 1);
		ft_putstr_fd(" : commande introuvable\n", 1);
		free(s);
		exit(127);
	}
	free(s);
	execve(((t_token *)token->content)->args[0], ((t_token *)token->content)->args, env_to_envp());
	exit(errno);
	return (0);
}

int		command_container(t_list *tokens_list)
{
	t_list	*token;
	char	*tmp;
	int		ret;
	int		status;
	int		i;

	i = 0;
	if (!(token = get_next_token(tokens_list)) || !token->content)
		return (0);
	while (builtins[i])
	{
		if (!ft_strcmp(((t_token *)token->content)->args[0], builtins[i]))
		{
			i = (g_builtins[i](((t_token *)token->content)->args));
			add_env("PIPESTATUS", (tmp = ft_itoa(i)));
			free(tmp);
			return (i);
		}
		i++;
	}
	if (!(i = fork()))
		ret = g_exec_token[((t_token *)token->content)->type](token);
	else
		waitpid(i, &status, 0);
	add_env("PIPESTATUS", (tmp = ft_itoa(WEXITSTATUS(status))));
	free(tmp);
	if (ret == 2 || !ret)
		return (0);
	return (1);
}
