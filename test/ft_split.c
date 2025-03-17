/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkurkar <mkurkar@student.42amman.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/26 21:30:04 by yaltayeh          #+#    #+#             */
/*   Updated: 2025/01/10 20:02:35 by mkurkar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	**ft_split_utils(const char *s, char *d, int i)
{
	char		**slices;
	char		*slice;
	const char	*start;

	while (*s && ft_strchr(d, *s))
		s++;
	start = s;
	while (*s && !ft_strchr(d, *s))
		s++;
	if (start == s)
		return (ft_calloc(i + 1, sizeof(char *)));
	slice = ft_strndup(start, s - start);
	if (!slice)
		return (NULL);
	slices = ft_split_utils(s + !!*s, d, i + 1);
	if (!slices)
	{
		free(slice);
		return (NULL);
	}
	slices[i] = slice;
	return (slices);
}

char	**ft_split(const char *s, char *d)
{
	if (!s || !d)
		return (NULL);
	return (ft_split_utils(s, d, 0));
}
