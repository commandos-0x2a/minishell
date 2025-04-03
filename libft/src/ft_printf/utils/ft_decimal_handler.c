/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_decimal_handler.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaltayeh <yaltayeh@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/14 00:25:28 by yaltayeh          #+#    #+#             */
/*   Updated: 2024/11/02 00:40:00 by yaltayeh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static size_t	ft_max(size_t a, size_t b)
{
	if (a > b)
		return (a);
	return (b);
}

static void	ft_decimal_helper1(int i32, size_t *count, t_printf_data data)
{
	size_t	blank_count;
	size_t	is_sign;

	is_sign = (i32 < 0 || (data.flags & (SPACE | PLUS)));
	blank_count = ft_blank_apply(data.numbers[0], \
					ft_max(data.numbers[1], *count) + is_sign, data.fd);
	if (i32 < 0)
		write(data.fd, "-", 1);
	else if (data.flags & PLUS)
		write(data.fd, "+", 1);
	else if (data.flags & SPACE)
		write(data.fd, " ", 1);
	*count += ft_zero_apply(data.numbers[1], *count, data.fd);
	*count += is_sign;
	*count += blank_count;
}

static void	ft_decimal_helper2(int i32, size_t *count, t_printf_data data)
{
	size_t	is_blank;

	is_blank = 0;
	if (i32 < 0 || (data.flags & (SPACE | PLUS)))
		is_blank = 1;
	if (data.flags & NUMBER)
		*count += ft_blank_apply(data.numbers[0], *count + is_blank, data.fd);
	if (i32 < 0)
		write(data.fd, "-", 1);
	else if (data.flags & PLUS)
		write(data.fd, "+", 1);
	else if (data.flags & SPACE)
		write(data.fd, " ", 1);
	if (data.flags & ZERO)
		*count += ft_zero_apply(data.numbers[0], *count + is_blank, data.fd);
	else if (data.flags & DOT)
		*count += ft_zero_apply(data.numbers[1], *count, data.fd);
	*count += is_blank;
}

size_t	ft_decimal_handle(t_printf_data data)
{
	char	*decimal;
	size_t	count;
	int		i32;

	count = 0;
	i32 = va_arg(*data.ap, int);
	decimal = ft_itoa(i32, 0);
	if (i32 || !(data.flags & DOT))
		count += ft_strlen(decimal);
	if ((data.flags & (ZERO | NUMBER)) && (data.flags & DOT))
		ft_decimal_helper1(i32, &count, data);
	else
		ft_decimal_helper2(i32, &count, data);
	if (i32 || !(data.flags & DOT))
		ft_putstr_fd(decimal, data.fd);
	if (data.flags & MINUS)
		count += ft_blank_apply(data.numbers[0], count, data.fd);
	free(decimal);
	return (count);
}
