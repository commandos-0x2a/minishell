/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaltayeh <yaltayeh@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/27 08:37:50 by yaltayeh          #+#    #+#             */
/*   Updated: 2024/11/02 00:46:18 by yaltayeh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	const char	*ptr;

	c &= 255;
	ptr = s + ft_strlen(s);
	while (ptr > s)
	{
		if (*ptr == c)
			return ((char *)ptr);
		ptr--;
	}
	if (*ptr == c)
		return ((char *)ptr);
	return (NULL);
}
