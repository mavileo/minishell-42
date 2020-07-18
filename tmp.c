/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tmp.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mavileo <mavileo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/25 05:34:08 by mavileo           #+#    #+#             */
/*   Updated: 2020/07/18 17:33:33 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_env	*env = NULL;
/* int		(*g_exec_token[]) () = {&ft_command, &ft_r_append, &ft_r_trunc,
								&ft_r_in, &ft_pipe,
								&ft_semicolon, &ft_and, &ft_or};  */
int		(*g_builtins[]) () = {&ft_echo, &ft_pwd, &ft_cd, &ft_export,
								&ft_unset, &ft_env, &ft_exit};
int		(*g_exec_token[]) () = {&ft_command, &ft_r_append, &ft_r_trunc, &ft_r_input, &ft_pipe};
char	*builtins[] = {"echo", "pwd", "cd", "export", "unset", "env", "exit", NULL};

int		main(int ac, char *av[], char *envp[])
{
	char	*input;
	t_list	*lst;
	//int		i;
	//t_list *token;

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
			lst = input_to_token_list(input);
			t_list *maillon;
			t_token *ttt;
			maillon = get_first_token(lst);
			if (!maillon)
				printf("get_first_token à renvoyé un maillon null.\n");
			else
			{
				ttt = maillon->content;
				printf("get_first_token: type: %d, args[0]: %s\n", ttt->type, ttt->args ? ttt->args[0] : "null");
			}
			maillon = get_next_token(maillon);
			if (!maillon)
				printf("get_next_token à renvoyé un maillon null.\n");
			else
			{
				ttt = maillon->content;
				printf("get_next_token: type: %d, args[0]: %s\n", ttt->type, ttt->args ? ttt->args[0] : "null");
			}
			maillon = get_next_token(maillon);
			if (!maillon)
				printf("get_next_token à renvoyé un maillon null.\n");
			else
			{
				ttt = maillon->content;
				printf("get_next_token: type: %d, args[0]: %s\n", ttt->type, ttt->args ? ttt->args[0] : "null");
			}
		//	tokens_container(lst);
			ft_lstclear(&lst, &ft_token_free);
		}
	}
	free_all_env();
	return (0);
}
