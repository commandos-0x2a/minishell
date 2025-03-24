/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dptr.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaltayeh <yaltayeh@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/24 13:05:17 by yaltayeh          #+#    #+#             */
/*   Updated: 2025/03/24 18:16:44 by yaltayeh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <libft.h>
#include <stdio.h>

void	free_dptr(char **ptr)
{
	char	**_ptr;

	if (!ptr)
		return ;
	_ptr = ptr;
	while (*_ptr)
		free(*_ptr++);
	free(ptr);
}

char	**copy_dptr(char **dptr)
{
	char	**ptr;
	char	**dst;

	ptr = dptr;
	while (*ptr)
		ptr++;
	dst = ft_calloc(ptr - dptr + 1, sizeof(char *));
	if (!dst)
		return (NULL);
	ptr = dst;
	while (*dptr)
	{
		*ptr = ft_strdup(*dptr++);
		if (*ptr == NULL)
		{
			free_dptr(dst);
			return (NULL);
		}
		ptr++;
	}
	return (dst);
}
