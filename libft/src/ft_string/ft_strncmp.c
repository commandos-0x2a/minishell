/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaltayeh <yaltayeh@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/27 08:03:54 by yaltayeh          #+#    #+#             */
/*   Updated: 2024/11/02 00:46:08 by yaltayeh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	const unsigned char	*_s1;
	const unsigned char	*_s2;
	size_t				i;

	i = 0;
	if (n == 0)
		return (0);
	_s1 = (const unsigned char *)s1;
	_s2 = (const unsigned char *)s2;
	while (_s1[i] == _s2[i] && _s1[i] && i < n - 1)
		i++;
	return (_s1[i] - _s2[i]);
}
