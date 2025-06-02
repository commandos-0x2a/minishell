/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaltayeh <yaltayeh@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/02 00:40:29 by yaltayeh          #+#    #+#             */
/*   Updated: 2025/06/02 22:31:59 by yaltayeh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_printf(const char *fmt, ...)
{
	va_list	ap;
	int		ret;

	va_start(ap, fmt);
	ret = ft_vfprintf(1, fmt, ap);
	va_end(ap);
	return (ret);
}

// int	ft_printf(const char *fmt, ...)
// {
// 	enum e_flags	flags;
// 	va_list			ap;
// 	int				count;
// 	size_t			numbers[2];

// 	va_start(ap, fmt);
// 	flags = NONE;
// 	count = 0;
// 	ft_bzero(numbers, sizeof(numbers));
// 	while (*fmt)
// 	{
// 		if (*fmt == '%')
// 		{
// 			fmt++;
// 			flags = ft_flags_parser(&fmt, numbers, NONE);
// 			if (ft_strchr(CONVENTIONS_CHARACTERS, *fmt))
// 				count += ft_printf_redirect(&ap, *fmt, flags, numbers);
// 			else
// 				count += ft_putchar(*fmt);
// 		}
// 		else
// 			count += ft_putchar(*fmt);
// 		fmt++;
// 	}
// 	return (count);
// }
