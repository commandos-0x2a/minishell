/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cut_slice.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaltayeh <yaltayeh@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/27 20:36:57 by yaltayeh          #+#    #+#             */
/*   Updated: 2025/04/27 21:17:51 by yaltayeh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>
#include <stdlib.h>

char	*cut_slice(char **s_r)
{
	char	*start;
	char	*s;

	s = *s_r;
	while (*s == ' ')
		s++;
	start = s;
	while (s && *s && *s != ' ')
	{
		if (*s == '\'' || *s == '\"')
			s = ft_strchr(s + 1, *s);
		if (s)
			s++;
	}
	*s_r = s;
	if (s == NULL)
		return (NULL);
	return (start);
}
