/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstinsert.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmouhali <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/05 13:13:10 by pmouhali          #+#    #+#             */
/*   Updated: 2020/07/25 03:52:50 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
**	Prends un maillon de liste chaînée en paramètre, et un element du même type.
**	Insert l'element new a la suite du maillon
**
**	BEFORE 	:	[elem]->[elem2]
**	AFTER	:	[elem]->[new_elem]->[elem2]
*/

void	ft_lstinsert(t_list *elem, t_list *new_elem)
{
	if (elem)
	{
		if (elem->next)
		{
			new_elem->next = elem->next;
			elem->next->prev = new_elem;
		}
		new_elem->prev = elem;
		elem->next = new_elem;
	}
	else
		elem = new_elem;
}
