/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_fprintf.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaltayeh <yaltayeh@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/02 00:40:23 by yaltayeh          #+#    #+#             */
/*   Updated: 2025/06/02 22:32:08 by yaltayeh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_fprintf(int fd, const char *fmt, ...)
{
	va_list	ap;
	int		ret;

	va_start(ap, fmt);
	ret = ft_vfprintf(fd, fmt, ap);
	va_end(ap);
	return (ret);
}
