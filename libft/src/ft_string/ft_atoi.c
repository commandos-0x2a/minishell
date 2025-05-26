/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaltayeh <yaltayeh@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/26 20:54:35 by yaltayeh          #+#    #+#             */
/*   Updated: 2025/05/26 15:10:30 by yaltayeh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <limits.h>

static int	add_check_overflow(int	*res, int a, int b)
{
	if ((b > 0 && a > INT_MAX - b) || (b < 0 && a < INT_MIN - b))
		return (-1);
	*res = a + b;
	return (0);
}

static int	multi_check_overflow(int *res, int a, int b)
{
	if ((a < 0 && b == INT_MIN) || (b < 0 && a == INT_MIN))
		return (-1);
	if (b != 0 && (a > INT_MAX / b || a < INT_MIN / b))
		return (-1);
	*res = a * b;
	return (0);
}

int	ft_atoi(const char *nptr)
{
	int	sign;
	int	ret;

	while (ft_isspace(*nptr))
		nptr++;
	sign = 1;
	if (*nptr == '-' || *nptr == '+')
	{
		if (*nptr == '-')
			sign = -1;
		nptr++;
	}
	ret = 0;
	while (ft_isdigit(*nptr))
	{
		ret = ret * 10 + *nptr - '0';
		nptr++;
	}
	return (ret * sign);
}

int	ft_atoi_r(const char **p_nptr)
{
	const char	*nptr;
	int			sign;
	int			ret;

	nptr = *p_nptr;
	while (ft_isspace(*nptr))
		nptr++;
	sign = 1;
	if (*nptr == '-' || *nptr == '+')
	{
		if (*nptr == '-')
			sign = -1;
		nptr++;
	}
	ret = 0;
	while (ft_isdigit(*nptr))
	{
		ret = ret * 10 + *nptr - '0';
		nptr++;
	}
	*p_nptr = nptr;
	return (ret * sign);
}

int	ft_atoi_save_r(char **p_nptr, int *res)
{
	char	*nptr;
	int		sign;

	nptr = *p_nptr;
	while (ft_isspace(*nptr))
		nptr++;
	sign = 1;
	if (*nptr == '-' || *nptr == '+')
	{
		if (*nptr == '-')
			sign = -1;
		nptr++;
	}
	*res = 0;
	while (ft_isdigit(*nptr))
	{
		if (multi_check_overflow(res, *res, 10))
			return (-1);
		if (add_check_overflow(res, *res, (*nptr - '0') * sign))
			return (-1);
		nptr++;
	}
	*p_nptr = nptr;
	return (0);
}
