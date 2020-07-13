/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mavileo <mavileo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/25 05:34:08 by mavileo           #+#    #+#             */
/*   Updated: 2020/07/13 12:20:32 by mavileo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_env	*env = NULL;
/* int		(*g_exec_token[]) () = {&ft_command, &ft_r_append, &ft_r_trunc,
								&ft_r_in, &ft_pipe,
								&ft_semicolon, &ft_and, &ft_or};  */
int		(*g_builtins[]) () = {&ft_echo, &ft_pwd, &ft_cd, &ft_export,
								&ft_unset, &ft_env, &ft_exit};
int		(*g_exec_token[]) () = {&ft_command};
char	*builtins[] = {"echo", "pwd", "cd", "export", "unset", "env", "exit", NULL};

t_fds	*init_fds(t_fds *fds)
{
	if (!(fds = malloc(sizeof(t_fds))))
		return (NULL);
	fds->prev[0] = 0;
	fds->prev[1] = 1;
	fds->actual[0] = 0;
	fds->actual[1] = 1;
	return (fds);
}

int		main(int ac, char *av[], char *envp[])
{
	char	*input;
	t_list	*lst;
	//int		i;
	//t_list *token;
	t_fds	*fds;

	(void)ac;
	(void)av;
	init_env(envp);
	while (1)
	{
		prompt();
		get_next_line(0, &input);
		if (!ft_strcmp(input, "q") || !ft_strcmp(input, "exit"))
			break;
		else
		{
			fds = init_fds(fds);
			lst = input_to_token_list(input);
			tokens_container(lst, fds);
			ft_lstclear(&lst, &ft_token_free);
		}
	}
	free_all_env();
	return (0);
}
