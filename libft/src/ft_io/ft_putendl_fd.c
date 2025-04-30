/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putendl_fd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaltayeh <yaltayeh@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/27 06:54:31 by yaltayeh          #+#    #+#             */
/*   Updated: 2024/12/18 17:29:09 by yaltayeh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_putendl_fd(char *s, int fd)
{
	int	ret;

	ret = 0;
	ret = ft_putstr_fd(s, fd);
	if (ret < 0)
		return (ret);
	ret += write(fd, "\n", 1);
	return (ret);
}
