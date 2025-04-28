/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dptr.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaltayeh <yaltayeh@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/24 13:05:17 by yaltayeh          #+#    #+#             */
/*   Updated: 2025/04/28 00:25:37 by yaltayeh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

char	**lst_2_dptr(t_list *lst)
{
	char		**dptr;
	static int	i;
	int			_i;

	_i = i++;
	if (!lst || !lst->str)
	{
		i = 0;
		return (ft_calloc(_i + 1, sizeof(char *)));
	}
	dptr = lst_2_dptr(lst->next);
	if (dptr)
		dptr[_i] = lst->str;
	return (dptr);
}
