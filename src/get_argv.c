/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_argv.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaltayeh <yaltayeh@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/09 19:32:20 by yaltayeh          #+#    #+#             */
/*   Updated: 2025/04/13 21:31:18 by yaltayeh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void lst_remove(t_list **lst, t_list *prev)
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

void	get_argv(t_list **lst)
{
	t_list	*prev;
	t_list	*cur;
	t_list	*start;

	cur = *lst;
	prev = NULL;
	start = NULL;
	while (cur && cur->str)
	{
		if (ft_strcmp(cur->str, "<<") == 0 \
			|| ft_strcmp(cur->str, "<") == 0 \
			|| ft_strcmp(cur->str, ">>") == 0 \
			|| ft_strcmp(cur->str, ">") == 0)
		{
			lst_remove(&cur, prev);
			lst_remove(&cur, prev);
			continue;
		}
		if (!prev)
			start = cur;
		prev = cur;
		cur = cur->next;
	}
	*lst = start;
}
