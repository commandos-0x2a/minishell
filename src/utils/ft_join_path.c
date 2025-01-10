/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_join_path.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaltayeh <yaltayeh@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/17 19:38:47 by yaltayeh          #+#    #+#             */
/*   Updated: 2025/01/09 12:46:22 by yaltayeh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_join_path(char *dest, const char *path1, const char *path2)
{
	size_t	len;

	len = ft_strlcpy(dest, path1, PATH_MAX);
	if (len >= PATH_MAX)
		return (len);
	if (dest[len - 1] != '/')
		ft_strlcat(dest, "/", PATH_MAX);
	len = ft_strlcat(dest, path2, PATH_MAX);
	return (len);
}
