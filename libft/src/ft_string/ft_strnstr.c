/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaltayeh <yaltayeh@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/26 21:22:42 by yaltayeh          #+#    #+#             */
/*   Updated: 2024/11/02 00:46:16 by yaltayeh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	size_t	i;
	size_t	l_len;

	i = 0;
	l_len = ft_strlen(needle);
	if (!l_len)
		return ((char *)haystack);
	while (haystack[i] && i <= len - l_len && (len >= l_len))
	{
		if (ft_strncmp(haystack + i, needle, l_len) == 0)
			return ((char *)(haystack + i));
		i++;
	}
	return (NULL);
}
