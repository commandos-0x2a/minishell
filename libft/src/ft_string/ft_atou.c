/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atou.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaltayeh <yaltayeh@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/02 00:42:39 by yaltayeh          #+#    #+#             */
/*   Updated: 2024/11/02 11:08:14 by yaltayeh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_atou(const char *nptr)
{
	size_t		ret;

	while (ft_isspace(*nptr))
		nptr++;
	ret = 0;
	while (ft_isdigit(*nptr))
	{
		ret = ret * 10 + *nptr - '0';
		nptr++;
	}
	return (ret);
}

size_t	ft_atou_r(const char **p_nptr)
{
	const char	*nptr;
	size_t		ret;

	nptr = *p_nptr;
	while (ft_isspace(*nptr))
		nptr++;
	ret = 0;
	while (ft_isdigit(*nptr))
	{
		ret = ret * 10 + *nptr - '0';
		nptr++;
	}
	*p_nptr = nptr;
	return (ret);
}
