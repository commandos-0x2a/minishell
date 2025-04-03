/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa_base.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaltayeh <yaltayeh@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/14 00:24:26 by yaltayeh          #+#    #+#             */
/*   Updated: 2024/11/02 00:44:17 by yaltayeh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	get_digit_count_lu(unsigned long n, int base)
{
	int	count;

	count = 0;
	if (base < 2)
		return (-1);
	if (n == 0)
		return (1);
	while (n)
	{
		n /= base;
		count++;
	}
	return (count);
}

char	*ft_itoa_base(unsigned long n, char *base_sym)
{
	char	*ret;
	int		digit_count;
	int		base;

	base = ft_strlen(base_sym);
	digit_count = get_digit_count_lu(n, base);
	if (digit_count == -1)
		return (NULL);
	ret = ft_calloc(digit_count + 1, sizeof(char));
	if (!ret)
		return (NULL);
	if (n == 0)
		ret[0] = '0';
	while (n)
	{
		ret[--digit_count] = base_sym[n % base];
		n /= base;
	}
	return (ret);
}
