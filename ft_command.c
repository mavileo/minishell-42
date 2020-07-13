/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_command.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mavileo <mavileo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/10 17:29:13 by mavileo           #+#    #+#             */
/*   Updated: 2020/07/13 02:31:01 by mavileo          ###   ########.fr       */
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

void	exec_bin(t_list *token, char **envp)
{
	char	*s;

	s = ft_strdup(((t_token *)token->content)->args[0]);
	if (get_abs_value(((t_token *)token->content)->args))
	{
		ft_putstr_fd(s, 1);
		ft_putstr_fd(" : commande introuvable\n", 1);
		free(s);
		free_envp(envp);
		free_all_env();
		ft_lstclear(&token, &ft_token_free);
		exit(127);
	}
	free(s);
	execve(((t_token *)token->content)->args[0], ((t_token *)token->content)->args, envp);
	free_all_env();
	ft_lstclear(&token, &ft_token_free);
	free_envp(envp);
	exit(errno);
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

int		ft_command(t_list *token)
{
	char	*tmp;
	int		ret;
	int		status;
	int		pid;
	char	**envp;

	envp = env_to_envp();
	if (!token->content)
		return (0);
	if (check_builtins(token))
	{
		free_envp(envp);
		return (ft_atoi(get_env_value("PIPESTATUS")));
	}
	if (!(pid = fork()))
		exec_bin(token, envp);
	else
		waitpid(pid, &status, 0);
	add_env("PIPESTATUS", (tmp = ft_itoa(WEXITSTATUS(status))));
	free_envp(envp);
	free(tmp);
	return (0);
}
