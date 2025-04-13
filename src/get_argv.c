/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_argv.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaltayeh <yaltayeh@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/09 19:32:20 by yaltayeh          #+#    #+#             */
/*   Updated: 2025/04/13 02:08:28 by yaltayeh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void lst_remove(t_tokens **lst, t_tokens *prev)
{
	t_tokens	*cur;

	if (!*lst)
		return ;

	cur = *lst;
	if (prev)
		prev->next = cur->next;
	*lst = cur->next;
	if (cur->token)
		free(cur->token);
	free(cur);
}

void	get_argv(t_tokens **lst)
{
	t_tokens	*prev;
	t_tokens	*cur;
	t_tokens	*start;

	cur = *lst;
	prev = NULL;
	start = NULL;
	while (cur && cur->token)
	{
		if (ft_strcmp(cur->token, "<<") == 0 \
			|| ft_strcmp(cur->token, "<") == 0 \
			|| ft_strcmp(cur->token, ">>") == 0 \
			|| ft_strcmp(cur->token, ">") == 0)
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
