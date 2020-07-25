/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstremove.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmouhali <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/05 13:13:10 by pmouhali          #+#    #+#             */
/*   Updated: 2020/07/25 03:53:09 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
**	Prends un maillon de liste chaînée en paramètre et le supprime.
**
**	BEFORE 	:   [elem-1]->[elem]->[elem1]
**	AFTER	:	[elem-1]->[elem1]
*/

void	ft_lstremove(t_list *elem, void (*delete)(void *e))
{
	if (!elem)
		return ;
	elem->next->prev = elem->prev;
	elem->prev = elem->next;
	elem->next = NULL;
	elem->prev = NULL;
	delete(elem);
	elem = NULL;
}
