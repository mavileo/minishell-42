/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mavileo <mavileo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/25 05:34:08 by mavileo           #+#    #+#             */
/*   Updated: 2020/07/20 07:33:20 by mavileo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_env	*env = NULL;

int		(*g_builtins[]) () = {&ft_echo, &ft_pwd, &ft_cd, &ft_export,
								&ft_unset, &ft_env, &ft_exit};
int		(*g_exec_token[]) () = {&ft_command, &ft_r_append, &ft_r_trunc,
								&ft_r_input, &ft_pipe};
char	*builtins[] = {"echo", "pwd", "cd", "export", "unset", "env", "exit", NULL};

int		main(int ac, char *av[], char *envp[])
{
	char	*input;
	t_list	*lst;
	char	run;
	//t_list *token;

	(void)ac;
	(void)av;
	init_env(envp);
	//signal(SIGINT, handle_ctrl_c);
	//signal(SIGQUIT, handle_ctrl_bs);
	run = 1;
	while (run)
	{
		prompt();
		get_next_line(0, &input);
		if (!ft_strcmp(input, "q") || !ft_strcmp(input, "exit"))
			run = 0;
		else
		{
			lst = input_to_token_list(input);
			if (lst == NULL) // c'est qu'il y a eu une syntax error donc
				add_env("PIPESTATUS", "2");				
			else
			{
				lst = commands_list(lst);	
				execute_commands(lst);
			}
		}
		free(input);
	}
	free_all_env();
	return (0);
}
