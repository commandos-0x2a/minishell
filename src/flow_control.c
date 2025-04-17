/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flow_control.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaltayeh <yaltayeh@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/13 02:19:13 by yaltayeh          #+#    #+#             */
/*   Updated: 2025/04/17 19:00:39 by yaltayeh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void set_null_token(t_list *lst, int *op)
{
	*op = 0;
	while (lst && lst->str)
	{
		if (ft_strcmp(lst->str, "&&") == 0 || \
			ft_strcmp(lst->str, "||") == 0)
		{
			if (ft_strcmp(lst->str, "&&") == 0)
				*op = 1;
			else if (ft_strcmp(lst->str, "||") == 0)
				*op = 2;
			free(lst->str);
			lst->str = NULL;
			return ;
		}
		lst = lst->next;
	}
}

int	flow_control(t_mini *mini)
{
	int			op;
	int			test;

	test = 1;
	while (mini->tokens && mini->tokens->str)
	{
		set_null_token(mini->tokens, &op);
		if (test)
		{
			if (pipeline_control(mini) == -1)
				return (-1);
			test = !mini->exit_status;
			if (op == 2)
				test = !test;
		}
		if (op == 0)
			break ;
		lst_move2next(&mini->tokens);
	}
	return (0);
}