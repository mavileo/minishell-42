/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_redirections.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mavileo <mavileo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/18 13:53:46 by user42            #+#    #+#             */
/*   Updated: 2020/07/22 20:34:59 by mavileo          ###   ########.fr       */
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

t_list	*retrieve_command(t_list *token)
{
	t_token *t;

	if (token->prev == NULL)
		return (NULL);
	while ((t = token->content) && t->type > COMMAND && t->type <= R_INPUT)
	{
/* 		write(1, "type : ", ft_strlen("type : "));
		write(1, ft_itoa(t->type), ft_strlen(ft_itoa(t->type)));
		write(1, "\nrgs[0] : ", ft_strlen("\nrgs[0] : "));
		write(1, t->args[0], ft_strlen(t->args[0]));
		write(1, "\n\n", 2);
 */		token = token->prev;		
	}
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

	stdout_s = dup(STDOUT_FILENO); // sauvegarde STDOUT
	filename = ((t_token*)token->content)->args[0]; // isole le nom du fichier à créer/ouvrir
	if ((f_fd = open(filename, O_WRONLY | O_CREAT | O_APPEND, 0666)) == -1) // ouvre/créer le fichier avec le bon flag O_APPEND
		return (-1);
	dup2(f_fd, STDOUT_FILENO); // transforme STDOUT en le fd du fichier obtenu
	if (token->next && ((t_token*)token->next->content)->type <= R_INPUT) // si next existe ET est de type redirection
		g_exec_token[((t_token*)token->next->content)->type](token->next, fds); // on execute next avec la bonne fonction (execution recursive des redirections successives)
	command = NULL; // set à NULL au cas le if du dessous est false
	if (!token->next || ((t_token*)token->next->content)->type > R_INPUT) // si next n'existe pas OU n'est pas de type redirection
		command = retrieve_command(token); // on remonte les ->prev jusqu'à trouver la commande de base (ex: $> ls > file1 >> file2 >> file 3 < input1: on remonte jusqu'à ls)
	if (command) // si on a effectivement trouvé une commande
		g_exec_token[COMMAND](command, fds); // on appel ft_command sur ce token command, si il n'y en a pas, on s'en fou, le fichier à été ouvert c'est ce qui compte
	dup2(stdout_s, STDOUT_FILENO); // on reset STDOUT à son fd d'origine
	printf("token : %d %s\n", ((t_token*)token->content)->type, ((t_token*)token->content)->args[0]);
	close(f_fd); // on ferme le fichier ouvert
	return (-1); // ?
}

int                     ft_r_trunc(t_list *token, t_fds *fds)
{
	int stdout_s;
	int f_fd;
	t_list *command;
	char *filename;

	stdout_s = dup(STDOUT_FILENO);
	filename = ((t_token*)token->content)->args[0];
	if ((f_fd = open(filename, O_WRONLY | O_CREAT | O_TRUNC, 0666)) == -1)
		return (-1);
	dup2(f_fd, STDOUT_FILENO);
	if (token->next && ((t_token*)token->next->content)->type <= R_INPUT)
		g_exec_token[((t_token*)token->next->content)->type](token->next, fds);
	command = NULL;
	if (!token->next || ((t_token*)token->next->content)->type > R_INPUT)
		command = retrieve_command(token);
	if (command)
		g_exec_token[COMMAND](command, fds);
	dup2(stdout_s, STDOUT_FILENO);
	printf("token trunc : %d %s\n", ((t_token*)command->content)->type, ((t_token*)command->content)->args[0]);
	close(f_fd);
	return (-1);
}

int                     ft_r_input(t_list *token, t_fds *fds)
{
	int stdin_s;
	int f_fd;
	t_list *command;
	char *filename;

	stdin_s = dup(STDIN_FILENO);
	filename = ((t_token*)token->content)->args[0];
	if ((f_fd = open(filename, O_RDONLY)) == -1) // seule redirection qui ne créer pas un fichier et qui renvoie donc une erreur si le file n'existe pas
	{
		ft_putstr_fd(filename, 2);
		ft_putstr_fd(": no such file or directory\n", 2);
		return (errno);
	}
	dup2(f_fd, STDIN_FILENO);
	if (token->next && ((t_token*)token->next->content)->type <= R_INPUT)
		g_exec_token[((t_token*)token->next->content)->type](token->next, fds);
	command = NULL;
	if (!token->next || ((t_token*)token->next->content)->type > R_INPUT)
		command = retrieve_command(token);
	if (command)
		g_exec_token[COMMAND](command, fds);
	dup2(stdin_s, STDIN_FILENO);
	close(f_fd);
	return (-1);
}
