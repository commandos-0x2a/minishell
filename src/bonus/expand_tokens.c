/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_tokens.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaltayeh <yaltayeh@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/21 14:16:31 by yaltayeh          #+#    #+#             */
/*   Updated: 2025/04/28 21:39:09 by yaltayeh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	tok_remove_qouts(t_list *lst)
{
	while (lst && lst->str)
	{
		remove_qouts(lst->str);
		lst = lst->next;
	}
}

static int	handle_wildcard(t_list **cur_r, t_list *last, char **slices)
{
	t_list	*cur;

	cur = *cur_r;
	last = last->next;
	while (cur && cur->str && cur != last)
	{
		slices = expand_wildcard(cur->str);
		if (!slices)
			return (-1);
		cur = lst_expand(cur, slices);
		free(slices);
		if (!cur)
			return (-1);
		cur = cur->next;
	}
	*cur_r = cur;
	return (0);
}

int	expand_tokens(t_mini *mini, t_list *lst)
{
	char	**slices;
	t_list	*last;
	t_list	*cur;

	cur = lst;
	while (cur && cur->str)
	{
		slices = expand_str(mini, cur->str);
		if (!slices)
			return (-1);
		last = lst_expand(cur, slices);
		free(slices);
		if (!last)
			return (-1);
		if (handle_wildcard(&cur, last, slices) != 0)
			return (-1);
	}
	tok_remove_qouts(lst);
	return (0);
}
