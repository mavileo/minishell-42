/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_redirections.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/18 13:53:46 by user42            #+#    #+#             */
/*   Updated: 2020/07/18 15:47:57 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
**	REDIRECTIONS
**
**	résumé des cas possibles :
**
**	$> ls | grep .c > list.txt
**	$> cat list.txt | rev >> troll.txt | cut -c1-3
**	$> grep .c << list.txt | cat -e
**	$> >> file.txt
**	$> grep carrots < filethatdoesntexist.c
**	$> grep "carrots" < potager.c > list.txt >> file.txt 
**
**
**	La commande (si il y en a une) se situera toujours à gauche de la rediretion.
**	Les trois fonctions suivront les mêmes étapes :
**
**	1. sauvegarder STDOUT ou STDIN
**	2. ouvrir le fichier, récupérer le fd
**	3. modifier STDIN ou STDOUT avec le fd obtenu
**	4. si le token suivant est une redirection, call
**	5. si le token suivant n'est pas une redirection, go back jusqu'à la commande, call ft_command
**		5.1 si aucune commande n'est trouvée, ne fais rien
**	6. restorer STDOUT ou STDIN
**	7. close le fd
**
**	Les restore/close sont gérés récursivement.
**	La dernière redirection execute la commande.
**	Donc tout les fichiers seront bien crées, et la bonne redirection sera effectuée.
**	Même sans commande, les redirections s'executent.
*/

static t_list	*retrieve_command(t_list *token)
{
	t_token *t;

	while ((t = token->content) && t->type > COMMAND && t->type <= R_INPUT)
		token = token->prev;
	if (t->type == COMMAND)
		return (token);
	else
		return (NULL);
}

int                     ft_r_append(t_list *token, t_fds *fds)
{
	int stdout_s;
	int f_fd;
	t_list *command;
	char *filename;

	// DEBBUG	
	printf("ft_r_append called.\n");
	// DEBBUG	
	stdout_s = dup(STDOUT_FILENO);
	filename = ((t_token*)token->content)->args[0];
	if ((f_fd = open(filename, O_WRONLY | O_CREAT | O_APPEND, 0666)) == -1)
		return (-1);
	dup2(f_fd, STDOUT_FILENO);
	if (((t_token*)token->next->content)->type <= R_INPUT) // si next est de type redirection
		g_exec_token[((t_token*)token->next->content)->type](token->next, fds);
	command = NULL;
	if (((t_token*)token->next->content)->type > R_INPUT) // si next n'est pas de type redirection
		command = retrieve_command(token);
	if (command)
		g_exec_token[COMMAND](command, fds);
	dup2(stdout_s, STDOUT_FILENO);
	close(f_fd);
	return (0); // ?
}

int                     ft_r_trunc(t_list *token, t_fds *fds)
{
	int stdout_s;
	int f_fd;
	t_list *command;
	char *filename;

	// DEBBUG	
	printf("ft_r_trunc called.\n");
	// DEBBUG	
	stdout_s = dup(STDOUT_FILENO);
	filename = ((t_token*)token->content)->args[0];
	if ((f_fd = open(filename, O_WRONLY | O_CREAT | O_TRUNC, 0666)) == -1)
		return (-1);
	dup2(f_fd, STDOUT_FILENO);
	if (((t_token*)token->next->content)->type <= R_INPUT) // si next est de type redirection
		g_exec_token[((t_token*)token->next->content)->type](token->next, fds);
	command = NULL;
	if (((t_token*)token->next->content)->type > R_INPUT) // si next n'est pas de type redirection
		command = retrieve_command(token);
	if (command)
		g_exec_token[COMMAND](command, fds);
	dup2(stdout_s, STDOUT_FILENO);
	close(f_fd);
	return (0); // ?
}

int                     ft_r_input(t_list *token, t_fds *fds)
{
	int stdin_s;
	int f_fd;
	t_list *command;
	char *filename;

	// DEBBUG	
	printf("ft_r_input called.\n");
	// DEBBUG	
	stdin_s = dup(STDIN_FILENO);
	filename = ((t_token*)token->content)->args[0];
	if ((f_fd = open(filename, O_RDONLY)) == -1)
	{
		ft_putstr_fd(filename, 2);
		ft_putstr_fd(": no such file or directory\n", 2);
		return (-1);
	}
	dup2(f_fd, STDIN_FILENO);
	if (((t_token*)token->next->content)->type <= R_INPUT) // si next est de type redirection
		g_exec_token[((t_token*)token->next->content)->type](token->next, fds);
	command = NULL;
	if (((t_token*)token->next->content)->type > R_INPUT) // si next n'est pas de type redirection
		command = retrieve_command(token);
	if (command)
		g_exec_token[COMMAND](command, fds);
	dup2(stdin_s, STDIN_FILENO);
	close(f_fd);
	return (0); // ?
}
