/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaltayeh <yaltayeh@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/26 21:30:04 by yaltayeh          #+#    #+#             */
/*   Updated: 2024/11/07 00:20:07 by yaltayeh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(int count, ...)
{
	size_t	len;
	char	*ret;
	va_list	ap;
	va_list	ap_copy;
	int		i;

	va_start(ap, count);
	va_copy(ap_copy, ap);
	i = 0;
	len = 0;
	while (i < count)
	{
		len += ft_strlen(va_arg(ap_copy, char *));
		i++;
	}
	ret = ft_calloc(len + 1, sizeof(char));
	i = 0;
	while (ret && i < count)
	{
		ft_strlcat(ret, va_arg(ap, char *), len + 1);
		i++;
	}
	va_end(ap);
	return (ret);
}
