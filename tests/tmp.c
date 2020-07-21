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

#include "../minishell.h"

t_env	*env = NULL;

int		(*g_builtins[]) () = {&ft_echo, &ft_pwd, &ft_cd, &ft_export,
								&ft_unset, &ft_env, &ft_exit};
int		(*g_exec_token[]) () = {&ft_command, &ft_r_append, &ft_r_trunc,
								&ft_r_input, &ft_pipe};
char	*builtins[] = {"echo", "pwd", "cd", "export", "unset", "env", "exit", NULL};



static t_list	*commands(t_list *tokens)
{
	t_list *head;
	t_list *commands;
	t_list *nlst;

	head = tokens;
	commands = NULL;
	nlst = NULL;
	while (tokens)
	{
		if (((t_token*)tokens->content)->type == SEMICOLON && nlst)
		{
			ft_lstadd_back(&commands, ft_lstnew(nlst));
			nlst = NULL;
		}
		else
			ft_lstadd_back(&nlst, ft_lstnew(ft_token_dup(tokens->content)));
		tokens = tokens->next;
	}
	if (nlst)
		ft_lstadd_back(&commands, ft_lstnew(nlst));
	ft_lstclear(&head, &ft_token_free);
	return (commands);
}

int		main(int ac, char *av[], char *envp[])
{
	char	*input;
	t_list	*lst;
	t_list	*tmp;
	t_list	*head;

	(void)ac;
	(void)av;
	init_env(envp);
	//signal(SIGINT, handle_ctrl_c);
	//signal(SIGQUIT, handle_ctrl_bs);
	prompt();
	get_next_line(0, &input);
	lst = input_to_token_list(input);
	if (lst == NULL) // c'est qu'il y a eu une syntax error donc
		add_env("PIPESTATUS", "2");				
	lst = commands(lst);	
	head = lst;
	while (lst)
	{
		tmp = lst->content;
//		tokens_container(tmp);
		ft_lstclear(&tmp, &ft_token_free);
		lst->content = NULL;
		lst = lst->next;
	}
	ft_lstclear(&head, free);
	free(input);
	free_all_env();
	return (0);
}
