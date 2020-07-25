/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_indexr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/25 03:50:39 by user42            #+#    #+#             */
/*   Updated: 2020/07/25 03:50:48 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
**	[NAME] :
**	ft_indexr
**	[DESCRIPTION] :
**	try to find character 'c' in string 's'.
**	[RETURN VALUE] :
**	returns the index where the last occurence of 'c' was found or -1.
*/

#include "libft.h"

int	ft_indexr(const char *s, int c)
{
	int i;

	i = ft_strlen(s);
	while (--i >= 0)
		if (s[i] == c)
			return (i);
	return (i);
}
