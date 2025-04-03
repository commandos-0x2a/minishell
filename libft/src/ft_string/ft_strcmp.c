/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaltayeh <yaltayeh@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/27 08:03:54 by yaltayeh          #+#    #+#             */
/*   Updated: 2024/11/03 14:37:36 by yaltayeh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strcmp(const char *s1, const char *s2)
{
	const unsigned char	*_s1;
	const unsigned char	*_s2;
	size_t				i;

	i = 0;
	_s1 = (const unsigned char *)s1;
	_s2 = (const unsigned char *)s2;
	while (_s1[i] == _s2[i] && _s1[i])
		i++;
	return (_s1[i] - _s2[i]);
}
