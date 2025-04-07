/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_argv.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaltayeh <yaltayeh@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/09 19:32:20 by yaltayeh          #+#    #+#             */
/*   Updated: 2025/04/07 20:38:06 by yaltayeh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void lst_remove(t_list **lst, t_list *prev)
{
	t_list	*node;

	if (!*lst)
		return ;

	node = *lst;
	if (prev)
		prev->next = node->next;
	*lst = node->next;
	free(node->token);
	free(node);
}

void	get_argv(t_list **lst_p)
{
	t_list	*prev;
	t_list	*lst;
	t_list	*start;

	lst = *lst_p;
	prev = NULL;
	start = NULL;
	while (lst && lst->token)
	{
		if (ft_strcmp(lst->token, "<<") == 0 \
			|| ft_strcmp(lst->token, "<") == 0 \
			|| ft_strcmp(lst->token, ">>") == 0 \
			|| ft_strcmp(lst->token, ">") == 0)
		{
			lst_remove(&lst, prev);
			lst_remove(&lst, prev);
			continue;
		}
		if (!prev)
			start = lst;
		prev = lst;
		lst = lst->next;
	}
	*lst_p = start;
}
