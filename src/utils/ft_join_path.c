/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_join_path.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkurkar <mkurkar@student.42amman.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/17 19:38:47 by yaltayeh          #+#    #+#             */
/*   Updated: 2025/01/10 20:02:52 by mkurkar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
