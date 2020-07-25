/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_display_error.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mavileo <mavileo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/25 01:28:00 by user42            #+#    #+#             */
/*   Updated: 2020/07/25 04:09:15 by mavileo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
** ft_display_error
**
** permet de simplifier la syntaxe quand on veut afficher une erreur
** en general on affiche 1 ou 2 element séparés donc elle prends 2 args
** si il y'a deux args elle affiche ": " entre les deux
**
** si on veut afficher un seul element, il faut le placer sur error_msg
**
** donc on obtient ce format de string : "something: some error"
*/

void	ft_dsplerr(char *arg, char *error_msg)
{
	if (arg)
		ft_putstr_fd(arg, STDERR_FILENO);
	if (arg && error_msg)
		ft_putstr_fd(": ", STDERR_FILENO);
	if (error_msg)
		ft_putendl_fd(error_msg, STDERR_FILENO);
}
