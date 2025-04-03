/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_redirect.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaltayeh <yaltayeh@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/08 19:54:29 by yaltayeh          #+#    #+#             */
/*   Updated: 2024/11/02 00:40:15 by yaltayeh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_printf_redirect(char conversions, t_printf_data data)
{
	if (conversions == 'c')
		return (ft_char_handle(data));
	else if (conversions == 's')
		return (ft_str_handle(data));
	else if (conversions == 'p')
		return (ft_pointer_handle(data));
	else if (conversions == 'd' || conversions == 'i')
		return (ft_decimal_handle(data));
	else if (conversions == 'x')
		return (ft_hex_handle(data, 0));
	else if (conversions == 'X')
		return (ft_hex_handle(data, 1));
	else if (conversions == 'u')
		return (ft_u_decimal_handle(data));
	else if (conversions == '%')
		return (ft_percent_handle(data));
	return (0);
}
