/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_list.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaltayeh <yaltayeh@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/07 17:59:57 by yaltayeh          #+#    #+#             */
/*   Updated: 2025/04/14 22:32:27 by yaltayeh         ###   ########.fr       */
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

t_list	*lst_expand(t_list *lst, char **slices)
{
	int		i;
	t_list	*next;

	if (*slices)
		free(lst->str);
	next = lst->next;
	lst->next = NULL;
	i = 0;
	while (slices[i])
	{
		lst->str = slices[i];
		i++;
		if (!slices[i])
			break;
		if (!lst->next)
			lst->next = ft_calloc(1, sizeof(t_list));
		if (!lst->next)
		{
			lst->next = next; // reconnect with root for clean it
			while (slices[i]) // free unused slices
				free(slices[i++]);
			return (NULL);
		}
		lst = lst->next;
	}
	lst->next = next; // reconnect with root
	return (lst);
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
