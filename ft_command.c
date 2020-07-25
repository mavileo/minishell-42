/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_command.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mavileo <mavileo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/10 17:29:13 by mavileo           #+#    #+#             */
/*   Updated: 2020/07/25 05:07:13 by mavileo          ###   ########.fr       */
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
	tmp = g_env;
	while (tmp)
	{
		i++;
		tmp = tmp->next;
	}
	if (!(res = malloc(sizeof(char *) * (i + 1))))
		return (NULL);
	tmp = g_env;
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

int		exec_bin(t_list *token, char **envp)
{
	char	*cmd_path;
	int		pid;

	cmd_path = get_abs_value(((t_token *)token->content)->args[0]);
	if (cmd_path == NULL)
	{
		ft_dsplerr(((t_token *)token->content)->args[0],
		"commande introuvable");
		add_env("PIPESTATUS", "127");
		ft_tabfree(envp);
		return (127);
	}
	if ((pid = (fork())) == 0)
	{
		execve(cmd_path, ((t_token *)token->content)->args, envp);
		exit(errno);
	}
	save_process_pid(pid);
	free(cmd_path);
	ft_tabfree(envp);
	return (-1);
}

int		check_builtins(t_list *token)
{
	int		i;
	char	*tmp;

	i = 0;
	while (g_builtins_list[i])
	{
		if (!ft_strcmp(((t_token *)token->content)->args[0],
			g_builtins_list[i]))
		{
			i = (g_builtins[i](((t_token *)token->content)->args));
			add_env("PIPESTATUS", (tmp = ft_itoa(i)));
			free(tmp);
			return (1);
		}
		i++;
	}
	return (0);
}

int		ft_command(t_list *token, t_fds *fds)
{
	char	**envp;

	envp = env_to_envp();
	(void)fds;
	if (!token->content)
		return (1);
	if (check_builtins(token))
	{
		ft_tabfree(envp);
		return (ft_atoi(get_env_value("PIPESTATUS")));
	}
	return (exec_bin(token, envp));
}
