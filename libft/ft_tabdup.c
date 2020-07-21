// 42 HEADER

#include "libft.h"

/*
 **	returns an allocated copy of the two-dimensional array given in argument
 **	for the duplication to work it needs to be given a duplication function
 */
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

void	**ft_tabdup(char *tab[], char *(*dup)(char *))
{
	void **copy;
	int i;

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
