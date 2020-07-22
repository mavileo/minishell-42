/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mavileo <mavileo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/25 05:34:08 by mavileo           #+#    #+#             */
/*   Updated: 2020/07/20 07:33:20 by mavileo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_input(void)
{
	char *input;
	char *tmp;
	char buffer[BUFFER_SIZE];
	int i;

	input = NULL;
	ft_memset(buffer, 0, BUFFER_SIZE);
	while (read(0, buffer, BUFFER_SIZE) != -1)
	{
		if (buffer[0] == 0)
		{
			free(input);
			return (NULL);
		}
		input = ft_strjoin_free(input, buffer, 1);
		i = ft_index(buffer, '\n');
		if (i != -1)
		{
			tmp = input;
			input = ft_substr(input, 0, i);
			free(tmp);
			return (input);
		}
	}
	return (NULL);
}
