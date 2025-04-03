/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_flags_apply.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaltayeh <yaltayeh@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/14 00:24:41 by yaltayeh          #+#    #+#             */
/*   Updated: 2024/11/02 00:40:03 by yaltayeh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

size_t	ft_sharp_apply(int upper, int fd)
{
	if (upper)
		ft_putstr_fd("0X", fd);
	else
		ft_putstr_fd("0x", fd);
	return (2);
}

size_t	ft_zero_apply(size_t num, size_t count, int fd)
{
	size_t	i;

	i = 0;
	while (num > count + i)
	{
		ft_putchar_fd('0', fd);
		i++;
	}
	return (i);
}

size_t	ft_blank_apply(size_t num, size_t count, int fd)
{
	size_t	i;

	i = 0;
	while (num > count + i)
	{
		ft_putchar_fd(' ', fd);
		i++;
	}
	return (i);
}
