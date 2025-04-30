/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_vfprintf.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaltayeh <yaltayeh@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/08 19:50:37 by yaltayeh          #+#    #+#             */
/*   Updated: 2024/11/02 00:40:52 by yaltayeh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_vfprintf(int fd, const char *fmt, va_list *ap)
{
	int				count;
	t_printf_data	data;

	ft_bzero(&data, sizeof(data));
	data.ap = ap;
	data.fd = fd;
	count = 0;
	while (*fmt)
	{
		if (*fmt == '%')
		{
			fmt++;
			data.flags = ft_flags_parser(&fmt, data.numbers, NONE);
			if (ft_strchr(CONVENTIONS_CHARACTERS, *fmt))
				count += ft_printf_redirect(*fmt, data);
			else
				count += ft_putchar_fd(*fmt, fd);
		}
		else
			count += ft_putchar_fd(*fmt, fd);
		fmt++;
	}
	return (count);
}
