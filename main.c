/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mavileo <mavileo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/25 05:34:08 by mavileo           #+#    #+#             */
/*   Updated: 2020/07/25 05:07:53 by mavileo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_env	*g_env = NULL;

int		(*g_builtins[]) () = {&ft_echo, &ft_pwd, &ft_cd, &ft_export,
	&ft_unset, &ft_env, &ft_exit};
int		(*g_exec_token[]) () = {&ft_command, &ft_r_append, &ft_r_trunc,
	&ft_r_input, &ft_pipe};
char	*g_builtins_list[] = {"echo", "pwd", "cd", "export", "unset",
	"env", "exit", NULL};

t_list *g_process_pids;

int		main(int ac, char *av[], char *envp[])
{
	char	*input;
	t_list	*lst;

	(void)ac;
	(void)av;
	init_env(envp);
	signal(SIGINT, handle_ctrl_c);
	signal(SIGQUIT, handle_ctrl_bs);
	while (TRUE)
	{
		prompt();
		if ((input = get_input()) == NULL)
			input = ft_strdup("exit");
		lst = input_to_token_list(input);
		lst = commands_list(lst);
		execute_commands(lst);
		ft_lstclear(&g_process_pids, free);
		g_process_pids = NULL;
		free(input);
	}
	free_all_env();
	return (0);
}
