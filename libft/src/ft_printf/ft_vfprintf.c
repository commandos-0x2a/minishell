/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_vfprintf.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaltayeh <yaltayeh@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/08 19:50:37 by yaltayeh          #+#    #+#             */
/*   Updated: 2025/06/04 21:13:32 by yaltayeh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_vfprintf(int fd, const char *fmt, va_list ap)
{
	char	*buf;
	int		n;
	size_t	size;
	va_list	ap2;
	ssize_t	res;

	va_copy(ap2, ap);
	n = ft_vsnprintf(NULL, 0, fmt, ap2);
	va_end(ap2);
	if (n < 0)
		return (-1);
	size = (size_t)n + 1;
	buf = malloc(size);
	if (!buf)
		return (-1);
	n = ft_vsnprintf(buf, size, fmt, ap);
	if (n < 0)
	{
		free(buf);
		return (-1);
	}
	res = write(fd, buf, size - 1);
	free(buf);
	return ((int)res);
}
