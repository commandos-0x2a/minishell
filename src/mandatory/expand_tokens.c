/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_tokens.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaltayeh <yaltayeh@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/04 21:29:22 by mkurkar           #+#    #+#             */
/*   Updated: 2025/04/25 01:44:05 by yaltayeh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	expand_tokens(t_mini *mini, t_list *lst)
{
	char	**slices;
	t_list	*cur;

	cur = lst;
	while (cur && cur->str)
	{
		slices = expand_str(mini, cur->str);
		if (!slices)
			return (-1);
		cur = lst_expand(cur, slices);
		free(slices);
		if (!cur)
			return (-1);
		cur = cur->next;
	}
	cur = lst;
	while (cur && cur->str)
	{
		remove_qouts(cur->str);
		cur = cur->next;
	}
	return (0);
}
