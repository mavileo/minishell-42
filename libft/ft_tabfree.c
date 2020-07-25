/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tabfree.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/25 03:52:12 by user42            #+#    #+#             */
/*   Updated: 2020/07/25 03:52:16 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
**	[NAME] :
**	ft_tabfree
**
**	[DESCRIPTION] :
** 	frees a previously allocated and null-terminated two-dimensional array
**
**	[RETURN VALUE] :
**	none
*/

void	ft_tabfree(char **tab)
{
	int i;

	i = -1;
	while (tab && tab[++i])
	{
		free(tab[i]);
		tab[i] = NULL;
	}
	free(tab);
}
