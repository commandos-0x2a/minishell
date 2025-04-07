/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tokpbrk.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaltayeh <yaltayeh@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/18 21:00:06 by yaltayeh          #+#    #+#             */
/*   Updated: 2025/04/07 13:23:01 by yaltayeh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdarg.h>
#include "libft.h"

char	**ft_tokpbrk(char **tokens, const char *strset, ...)
{
	va_list		ap;
	va_list		ap2;
	const char	*str;

	va_start(ap, strset);
	while (*tokens)
	{
		va_copy(ap2, ap);
		str = strset;
		while (str)
		{
			if (ft_strcmp(*tokens, str) == 0)
			{
				va_end(ap);
				va_end(ap2);
				return (tokens);
			}
			str = va_arg(ap2, const char *);
		}
		va_end(ap2);
		tokens++;
	}
	va_end(ap);
	return (tokens);
}