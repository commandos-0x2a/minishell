/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flow_control.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaltayeh <yaltayeh@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/13 02:19:13 by yaltayeh          #+#    #+#             */
/*   Updated: 2025/04/13 17:42:12 by yaltayeh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void set_null_token(t_tokens *lst, int *op)
{
	*op = 0;
	while (lst && lst->token)
	{
		if (ft_strcmp(lst->token, "&&") == 0 || \
			ft_strcmp(lst->token, "||") == 0)
		{
			if (ft_strcmp(lst->token, "&&") == 0)
				*op = 1;
			else if (ft_strcmp(lst->token, "||") == 0)
				*op = 2;
			free(lst->token);
			lst->token = NULL;
			return ;
		}
		lst = lst->next;
	}
}

int	flow_control(t_mini *mini)
{
	int			op;
	int			test;

	(void)test;
	test = 1;
	while (mini->tokens && mini->tokens->token)
	{
		set_null_token(mini->tokens, &op);
		if (test)
		{
			test = !pipeline_control(mini);
			if (op == 2)
				test = !test;	
		}
		if (op == 0)
			break ;
		tok_move2next(&mini->tokens);
	}
	return (0);
}