// 42 HEADER

#include "libft.h"

/*
**	[NAME] :
**	ft_tabpush
**
**	[DESCRIPTION] :
**	creates a copy of the given two-dimensional array with the given string
**	to push added at the end of the array.
**
**	if the given string to push if null or empty, nothing is done
**
**	this function frees the given two-dimensional array, so it needs to be
**	previously allocated.
**
**	[RETURN VALUE] :
**	returns the new two-dimensional array, or, NULL if one parameter is null or
**	if allocation fail.
*/

static int	ft_tablen(const char *tab[])
{
	int i;

	if (tab == NULL)
		return (-1);
	i = 0;
	while (tab[i])
		i++;
	return (i);
}

char	**ft_tabpush(char *tab[], const char *s)
{
	char **copy;
	int len;
	int i;

	if (!s || s[0] == 0)
		return (tab);
	len = tab ? ft_tablen((const char **)tab) + 1 : 1;
	if (!(copy = (char**)malloc(sizeof(*tab) * (len + 1))))
		return (NULL);
	i = -1;
	while (tab && tab[++i])
		copy[i] = ft_strdup(tab[i]);
	copy[len - 1] = ft_strdup(s);
	copy[len] = NULL;
	ft_tabfree(tab);
	return (copy);
}
