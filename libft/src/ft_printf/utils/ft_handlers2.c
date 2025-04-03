/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_handlers2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaltayeh <yaltayeh@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/14 00:25:15 by yaltayeh          #+#    #+#             */
/*   Updated: 2024/11/02 00:40:11 by yaltayeh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static void	ft_hex_helper(unsigned int u32, size_t *count, t_printf_data data)
{
	if (data.flags & ZERO)
		*count += ft_zero_apply(data.numbers[0], *count, data.fd);
	if (data.flags & DOT)
		*count += ft_zero_apply(data.numbers[1], *count, data.fd);
	if (data.flags & SHARP && u32)
		*count += 2;
	if (data.flags & NUMBER && !(data.flags & (DOT | ZERO)))
		*count += ft_blank_apply(data.numbers[0], *count, data.fd);
}

size_t	ft_hex_handle(t_printf_data data, int upper)
{
	char			*hex;
	size_t			count;
	size_t			len;
	unsigned int	u32;

	u32 = va_arg(*data.ap, unsigned int);
	count = 0;
	if (upper)
		hex = ft_itoa_base(u32, HEX_BASE_UPPER);
	else
		hex = ft_itoa_base(u32, HEX_BASE);
	len = ft_strlen(hex);
	count += len;
	ft_hex_helper(u32, &count, data);
	if (data.flags & SHARP && u32)
		ft_sharp_apply(upper, data.fd);
	ft_putstr_fd(hex, data.fd);
	if (data.flags & MINUS)
		count += ft_blank_apply(data.numbers[0], count, data.fd);
	free(hex);
	return (count);
}

size_t	ft_percent_handle(t_printf_data data)
{
	ft_putchar_fd('%', data.fd);
	return (1);
}
