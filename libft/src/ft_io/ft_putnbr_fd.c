/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaltayeh <yaltayeh@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/27 06:53:34 by yaltayeh          #+#    #+#             */
/*   Updated: 2024/11/02 00:38:51 by yaltayeh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_putnbr_fd(int n, int fd)
{
	long	num;
	size_t	count;

	num = n;
	count = 0;
	if (num < 0)
	{
		count += ft_putchar_fd('-', fd);
		num *= -1;
	}
	if (num <= 9)
	{
		count += ft_putchar_fd(num + '0', fd);
	}
	else
	{
		count += ft_putnbr_fd(num / 10, fd);
		count += ft_putnbr_fd(num % 10, fd);
	}
	return (count);
}
