// 42 HEADER

/*
**	[NAME] :
**	ft_tabindex
**
**  [DESCRIPTION] :
**	use the ft_strcmp() function to find a given string inside the given
**	two-dimensional array.
**
**	[RETURN VALUE] :
**	returns the index where string 's' was found or -1.
**
*/

#include "libft.h"

int		ft_tabindex(const char *tab[], const char *s)
{
	int i;

	i = -1;
	while (tab[++i])
		if (ft_strcmp(tab[i], s) == 0)
			return (i);
	return (-1);
}
