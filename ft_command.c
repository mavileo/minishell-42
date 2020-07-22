/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_command.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mavileo <mavileo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/10 17:29:13 by mavileo           #+#    #+#             */
/*   Updated: 2020/07/19 18:52:14 by mavileo          ###   ########.fr       */
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

void	free_envp(char **envp)
{
	int i;

	i = 0;
	while (envp[i])
		free(envp[i++]);
	free(envp);

}

int		exec_bin(t_list *token, char **envp)
{
	char	*s;
	int		pid;

	s = ft_strdup(((t_token *)token->content)->args[0]);
	if (get_abs_value(((t_token *)token->content)->args))
	{
		ft_putstr_fd(s, STDERR_FILENO);
		ft_putstr_fd(" : commande introuvable\n", STDERR_FILENO);
		free(s);
		add_env("PIPESTATUS", (s = ft_itoa(127)));
		free(s);
		free_envp(envp);
		return (127);
	}
	free(s);
	if ((pid = (fork())) == 0)
	{
		execve(((t_token *)token->content)->args[0], ((t_token *)token->content)->args, envp);
		exit(errno);
	}
	save_process_pid(pid);
	free_envp(envp);
	return (-1);
}

int		check_builtins(t_list *token)
{
	int		i;
	char	*tmp;

	i = 0;
	while (builtins[i])
	{
		if (!ft_strcmp(((t_token *)token->content)->args[0], builtins[i]))
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
//	int		status;
//	int		pid;
	char	**envp;

	add_env("PIPESTATUS", "0");
	if (!ft_strcmp(((t_token *)token->content)->args[0], "..") ||
		!ft_strcmp(((t_token *)token->content)->args[0], "."))
	{
		ft_putstr_fd(((t_token *)token->content)->args[0], STDERR_FILENO);
		ft_putstr_fd(" : commande introuvable\n", STDERR_FILENO);
		add_env("PIPESTATUS", "127");
		return (0);
	}
	envp = env_to_envp();
//	status = 0;
	(void)fds;
	if (!token->content)
		return (1);
	if (check_builtins(token))
	{
		free_envp(envp);
		return (ft_atoi(get_env_value("PIPESTATUS")));
	}
	return (exec_bin(token, envp));
}
