/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaltayeh <yaltayeh@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/26 21:30:04 by yaltayeh          #+#    #+#             */
/*   Updated: 2025/03/18 17:17:08 by yaltayeh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <string.h>

static char	**ft_split_iter(const char *s, char *d, int i)
{
	char		**slices;
	char		*slice;
	const char	*start;

	while (*s && strchr(d, *s))
		s++;
	start = s;
	while (*s && !strchr(d, *s))
		s++;
	if (start == s)
		return (calloc(i + 1, sizeof(char *)));
	slice = strndup(start, s - start);
	if (!slice)
		return (NULL);
	slices = ft_split_iter(s + !!*s, d, i + 1);
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
	return (ft_split_iter(s, d, 0));
}
