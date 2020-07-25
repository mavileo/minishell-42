/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_reassign.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/25 03:54:01 by user42            #+#    #+#             */
/*   Updated: 2020/07/25 03:54:19 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
**	Prends deux pointeurs en paramètres.
**	Free le premier. Renvoie le deuxième.
**
**	Sert à réassigner des pointeurs alloués sans créer de leaks.
**
**	Exemple :
**
**	oldstr = ft_reassign(oldstr, newstr);
*/

void	*ft_reassign(void *oldptr, void *newptr)
{
	free(oldptr);
	return (newptr);
}
