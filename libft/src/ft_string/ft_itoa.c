/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaltayeh <yaltayeh@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/26 20:46:41 by yaltayeh          #+#    #+#             */
/*   Updated: 2025/04/28 00:05:24 by yaltayeh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	get_digit_count(int n, int base)
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

char	*ft_itoa(int n, int with_sign)
{
	char	*ret;
	int		digit_count;
	long	num;

	digit_count = get_digit_count(n, 10) + !!with_sign;
	ret = ft_calloc(digit_count + 1, sizeof(char));
	if (!ret)
		return (NULL);
	num = n;
	if (num < 0)
	{
		num *= -1;
		if (with_sign)
			ret[0] = '-';
	}
	if (num == 0)
		ret[0] = '0';
	while (num)
	{
		ret[--digit_count] = '0' + (num % 10);
		num /= 10;
	}
	return (ret);
}

static int	ft_get_digits_len(int n)
{
	int	len;

	len = 1;
	if (n < 0)
	{
		len++;
		n *= -1;
	}
	while (n / 10 != 0)
	{
		len++;
		n /= 10;
	}
	return (len);
}

static char	*ft_build_str(int n, int len, int sign)
{
	char	*str;
	int		i;

	str = (char *)malloc(sizeof(char) * (len + 1));
	if (!str)
		return (NULL);
	str[len] = '\0';
	i = len - 1;
	while (n > 9)
	{
		str[i] = (n % 10) + '0';
		n /= 10;
		i--;
	}
	str[i] = n + '0';
	if (sign)
		str[0] = '-';
	return (str);
}

char	*ft_itoa_kur(int n)
{
	int		len;
	int		sign;
	char	*str;

	len = 1;
	sign = 0;
	if (n == -2147483648LL)
		return (ft_strdup("-2147483648"));
	if (n < 0)
	{
		sign = 1;
		n *= -1;
	}
	len = ft_get_digits_len(n) + sign;
	str = ft_build_str(n, len, sign);
	return (str);
}
