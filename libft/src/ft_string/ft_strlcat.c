/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaltayeh <yaltayeh@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/26 21:13:29 by yaltayeh          #+#    #+#             */
/*   Updated: 2024/11/16 13:18:29 by yaltayeh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dest, const char *src, size_t size)
{
	size_t		dlen;
	size_t		slen;

	dlen = ft_strlen(dest);
	slen = ft_strlen(src);
	if (size <= dlen)
		return (dlen + slen);
	size -= dlen;
	dest += dlen;
	while (*src != '\0' && size > 1)
	{
		*dest++ = *src++;
		size--;
	}
	*dest = '\0';
	return (dlen + slen);
}
