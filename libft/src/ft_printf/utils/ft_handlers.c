/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_handlers.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaltayeh <yaltayeh@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/14 00:25:04 by yaltayeh          #+#    #+#             */
/*   Updated: 2024/11/07 00:16:54 by yaltayeh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

size_t	ft_char_handle(t_printf_data data)
{
	size_t	count;
	char	c;

	count = 0;
	c = va_arg(*data.ap, int);
	if (data.flags & NUMBER && !(data.flags & MINUS))
		count += ft_blank_apply(data.numbers[0], 1, data.fd);
	write(data.fd, &c, 1);
	if (data.flags & MINUS)
		count += ft_blank_apply(data.numbers[0], 1, data.fd);
	return (count + 1);
}

size_t	ft_str_handle(t_printf_data data)
{
	size_t	count;
	size_t	len;
	char	*s;

	s = (char *)va_arg(*data.ap, char *);
	count = 0;
	if (!s)
	{
		s = "(null)";
		if (data.numbers[1] < 6)
			data.numbers[1] = 0;
	}
	len = ft_strlen(s);
	if (data.flags & DOT && len > data.numbers[1])
		len = data.numbers[1];
	count += len;
	if (data.flags & (NUMBER | ZERO) && !(data.flags & MINUS))
		count += ft_blank_apply(data.numbers[0], count, data.fd);
	write(data.fd, s, len);
	if (data.flags & MINUS)
		count += ft_blank_apply(data.numbers[0], count, data.fd);
	return (count);
}

size_t	ft_pointer_handle(t_printf_data data)
{
	char			*hex;
	char			*str;
	size_t			count;
	unsigned long	addr;

	addr = (unsigned long)va_arg(*data.ap, void *);
	if (!addr)
		str = ft_strdup("(nil)");
	else
	{
		hex = ft_itoa_base(addr, HEX_BASE);
		if (!hex)
			return (0);
		str = ft_strjoin(2, "0x", hex);
		free(hex);
	}
	if (!str)
		return (0);
	count = ft_strlen(str);
	if (data.flags & NUMBER)
		count += ft_blank_apply(data.numbers[0], count, data.fd);
	ft_putstr_fd(str, data.fd);
	if (data.flags & MINUS)
		count += ft_blank_apply(data.numbers[0], count, data.fd);
	return (free(str), count);
}
