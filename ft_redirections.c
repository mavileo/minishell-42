/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_redirections.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/18 13:53:46 by user42            #+#    #+#             */
/*   Updated: 2020/07/18 14:13:04 by user42           ###   ########.fr       */
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
**
**
**
*/

int                     ft_r_append(t_list *token, t_fds *fds)
{

}

int                     ft_r_trunc(t_list *token, t_fds *fds);
int                     ft_r_in(t_list *token, t_fds *fds);
