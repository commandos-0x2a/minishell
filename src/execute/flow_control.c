/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flow_control.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaltayeh <yaltayeh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/07 08:13:50 by yaltayeh          #+#    #+#             */
/*   Updated: 2025/04/30 08:51:58 by yaltayeh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	set_null_token(t_list *lst, int *op)
{
	*op = 0;
	while (lst && lst->str)
	{
		if (ft_strcmp(lst->str, "&&") == 0
			|| ft_strcmp(lst->str, "||") == 0)
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
			if (op == 1)
				test = !mini->exit_status;
			else if (op == 2)
				test = mini->exit_status;
		}
		if (op == 0)
			break ;
		if (op == 2)
			test = !test;
		lst_move2next(&mini->tokens);
	}
	return (0);
}
