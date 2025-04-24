/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_list.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaltayeh <yaltayeh@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/07 17:59:57 by yaltayeh          #+#    #+#             */
/*   Updated: 2025/04/23 22:19:04 by yaltayeh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	lst_remove_one(t_list **lst, t_list *prev)
{
	t_list	*cur;

	if (!*lst)
		return ;
	cur = *lst;
	if (prev)
		prev->next = cur->next;
	*lst = cur->next;
	if (cur->str)
		free(cur->str);
	free(cur);
}

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
			break ;
		if (!lst->next)
			lst->next = ft_calloc(1, sizeof(t_list));
		if (!lst->next)
		{
			lst->next = next;
			while (slices[i])
				free(slices[i++]);
			return (NULL);
		}
		lst = lst->next;
	}
	lst->next = next;
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

t_list	*expand_tokens_2lst(t_mini *mini, const char *str)
{
	t_list	*lst;

	lst = ft_calloc(1, sizeof(*lst));
	if (!lst)
		return (NULL);
	lst->str = ft_strdup(str);
	if (!lst->str)
	{
		lst_clean(&lst);
		return (NULL);
	}
	if (expand_tokens(mini, lst) != 0)
	{
		lst_clean(&lst);
		return (NULL);
	}
	return (lst);
}
