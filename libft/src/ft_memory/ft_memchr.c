/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaltayeh <yaltayeh@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/27 07:00:11 by yaltayeh          #+#    #+#             */
/*   Updated: 2024/11/02 00:39:28 by yaltayeh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	size_t	i;

	c &= 255;
	i = 0;
	while (i < n)
	{
		if (((unsigned char *)s)[i] == c)
			return ((void *)s + i);
		i++;
	}
	return (NULL);
}
