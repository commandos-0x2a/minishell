/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaltayeh <yaltayeh@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/07 17:59:57 by yaltayeh          #+#    #+#             */
/*   Updated: 2025/04/14 06:20:18 by yaltayeh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	*lst_clean(t_list **lst)
{
	t_list	*next;

	while (*lst)
	{
		free((*lst)->str);
		next = (*lst)->next;
		free(*lst);
		*lst = next;
	}
	return (NULL);
}

void	*lst_move2next(t_list **lst)
{
	t_list	*next;

	while (*lst && (*lst)->str)
	{
		free((*lst)->str);
		next = (*lst)->next;
		free(*lst);
		*lst = next;
	}
	if (*lst)
	{
		next = (*lst)->next;
		free(*lst);
		*lst = next;
	}
	return (*lst);
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
