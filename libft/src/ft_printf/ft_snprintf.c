/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_snprintf.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaltayeh <yaltayeh@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/24 19:33:34 by mkurkar           #+#    #+#             */
/*   Updated: 2025/05/31 10:43:58 by yaltayeh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

/**
 * @brief Custom implementation of snprintf for integer and string conversion
 * @param buf Output buffer
 * @param size Buffer size
 * @param format Format string (supports %d and %s)
 * @param ... Variable arguments
 * @return Number of characters written (excluding null terminator)
 */
int	ft_snprintf(char *buf, size_t size, const char *format, ...)
{
	va_list	ap;
	int		ret;

	va_start(ap, format);
	ret = ft_vsnprintf(buf, size, format, ap);
	va_end(ap);
	return (ret);
}
