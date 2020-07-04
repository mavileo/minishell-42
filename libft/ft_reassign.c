// 42 HEADER

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
