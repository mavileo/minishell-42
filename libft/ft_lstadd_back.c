/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_front.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmouhali <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/05 13:13:10 by pmouhali          #+#    #+#             */
/*   Updated: 2019/11/05 14:12:12 by pmouhali         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstadd_back(t_list **alst, t_list *new)
{
	t_list *last_elem;

	if (*alst)
	{
		last_elem = ft_lstlast(*alst);
		last_elem->next = new;
		new->prev = last_elem;
	}
	else
		*alst = new;
}
