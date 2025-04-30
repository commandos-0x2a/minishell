/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_line.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaltayeh <yaltayeh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/24 12:13:24 by yaltayeh          #+#    #+#             */
/*   Updated: 2025/04/30 09:09:16 by yaltayeh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static size_t	operation_len(const char *s)
{
	if (ft_strncmp(s, "&&", 2) == 0 || ft_strncmp(s, "||", 2) == 0
		|| ft_strncmp(s, ">>", 2) == 0 || ft_strncmp(s, "<<", 2) == 0)
		return (2);
	else if (*s == '|' || *s == '<' || *s == '>')
		return (1);
	return (0);
}

static char	*allocate_expanded_line(const char *s)
{
	size_t	len;
	size_t	op_len;

	len = 0;
	while (*s)
	{
		op_len = operation_len(s);
		if (op_len)
			len += 2;
		len += op_len;
		s += op_len;
		len++;
		s++;
	}
	return (malloc(++len));
}

char	*expand_line(const char *s)
{
	char	*line;
	char	*s2;
	size_t	op_len;

	line = allocate_expanded_line(s);
	if (!line)
		return (NULL);
	s2 = line;
	while (*s)
	{
		op_len = operation_len(s);
		if (op_len)
		{
			*s2++ = ' ';
			while (op_len--)
				*s2++ = *s++;
			*s2++ = ' ';
		}
		*s2++ = *s++;
	}
	*s2 = '\0';
	return (line);
}
