/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tabdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/25 03:49:32 by user42            #+#    #+#             */
/*   Updated: 2020/07/25 03:50:23 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_tablen(char *tab[])
{
	int i;

	if (tab == NULL)
		return (-1);
	i = 0;
	while (tab[i])
		i++;
	return (i);
}

void		**ft_tabdup(char *tab[], char *(*dup)(char *))
{
	void	**copy;
	int		i;

	if (tab == NULL)
		return (NULL);
	if (!(copy = (void**)malloc(sizeof(*tab) * (ft_tablen(tab) + 1))))
		return (NULL);
	i = -1;
	while (tab[++i])
		copy[i] = dup(tab[i]);
	copy[i] = NULL;
	return (copy);
}
