/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaltayeh <yaltayeh@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/07 17:59:57 by yaltayeh          #+#    #+#             */
/*   Updated: 2025/04/13 21:31:18 by yaltayeh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	*tok_clean(t_list **lst)
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

void	*tok_move2next(t_list **lst)
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

