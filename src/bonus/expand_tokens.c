/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_tokens.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaltayeh <yaltayeh@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/21 14:16:31 by yaltayeh          #+#    #+#             */
/*   Updated: 2025/04/25 01:44:30 by yaltayeh         ###   ########.fr       */
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

int	expand_tokens(t_mini *mini, t_list *lst)
{
	char	**slices;
	t_list	*end;
	t_list	*cur;

	cur = lst;
	while (cur && cur->str)
	{
		slices = expand_str(mini, cur->str);
		if (!slices)
			return (-1);
		end = lst_expand(cur, slices);
		free(slices);
		if (!end)
			return (-1);
		end = end->next;
		while (cur && cur->str && cur != end)
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
	}
	tok_remove_qouts(lst);
	return (0);
}
