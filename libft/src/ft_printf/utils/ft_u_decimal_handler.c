/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_u_decimal_handler.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaltayeh <yaltayeh@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/14 00:25:28 by yaltayeh          #+#    #+#             */
/*   Updated: 2025/04/28 00:08:03 by yaltayeh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static size_t	ft_max(size_t a, size_t b)
{
	if (a > b)
		return (a);
	return (b);
}

static void	ft_u_decimal_helper1(size_t *count, t_printf_data data)
{
	size_t	blank_count;

	blank_count = ft_blank_apply(data.numbers[0],
			ft_max(data.numbers[1], *count), data.fd);
	*count += ft_zero_apply(data.numbers[1], *count, data.fd);
	*count += blank_count;
}

static void	ft_u_decimal_helper2(size_t *count, t_printf_data data)
{
	if (data.flags & NUMBER)
		*count += ft_blank_apply(data.numbers[0], *count, data.fd);
	if (data.flags & ZERO)
		*count += ft_zero_apply(data.numbers[0], *count, data.fd);
	else if (data.flags & DOT)
		*count += ft_zero_apply(data.numbers[1], *count, data.fd);
}

size_t	ft_u_decimal_handle(t_printf_data data)
{
	char			*decimal;
	size_t			count;
	unsigned int	u32;

	u32 = va_arg(*data.ap, unsigned int);
	count = 0;
	decimal = ft_itoa_base((unsigned long)u32, DECIMAL_BASE);
	if (u32 || !(data.flags & DOT))
		count += ft_strlen(decimal);
	if ((data.flags & (ZERO | NUMBER)) && (data.flags & DOT))
		ft_u_decimal_helper1(&count, data);
	else
		ft_u_decimal_helper2(&count, data);
	if (u32 || !(data.flags & DOT))
		ft_putstr_fd(decimal, data.fd);
	if (data.flags & MINUS)
		count += ft_blank_apply(data.numbers[0], count, data.fd);
	free(decimal);
	return (count);
}
