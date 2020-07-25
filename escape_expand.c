/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   escape_expand.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/24 16:29:44 by user42            #+#    #+#             */
/*   Updated: 2020/07/25 04:15:16 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static unsigned int	expand(char **old, unsigned int i)
{
	char			*start;
	char			*varvalue;
	char			*varname;
	unsigned int	j;

	j = 1;
	while (ft_isalnum((int)(*old)[i + j]) || (*old)[i + j] == '_')
		j++;
	if (j == 1 && ft_index("?'\"", (*old)[i + j]) == -1)
		return (i + 1);
	if ((*old)[i + 1] == '?' && ++j)
		varname = ft_strdup("PIPESTATUS");
	else
		varname = ft_substr(*old, i + 1, j - 1);
	if (!(varvalue = get_env_value(varname)))
	{
		ft_memmove(&(*old)[i], &(*old)[i + j], ft_strlen(&(*old)[i + j]) + 1);
		free(varname);
		return (i);
	}
	free(varname);
	start = ft_strjoin_free(ft_substr(*old, 0, i), varvalue, 1);
	start = ft_strjoin_free(start, &(*old)[i + j], 1);
	*old = ft_reassign(*old, start);
	return (i + ft_strlen(varvalue) - 1);
}

char				*escape_expand(const char *str)
{
	char			*s;
	unsigned int	i;
	char			q;

	q = 0;
	i = 0;
	s = ft_strdup(str);
	while (s[i])
	{
		quotes_onoff(&q, s[i]);
		if (s[i] == '"' || s[i] == '\'')
		{
			ft_memmove(&s[i], &s[i + 1], ft_strlen(s) - i);
			i--;
		}
		else if (s[i] == '\\'
			&& ((q == 0 || (q == '"' && ft_index("\\$\"", s[i + 1]) != -1))))
			ft_memmove(&s[i], &s[i + 1], ft_strlen(s) - i);
		else if (s[i] == '$' && q != '\'')
			i = expand(&s, i) - 1;
		i++;
	}
	return (s);
}
