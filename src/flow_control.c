/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flow_control.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaltayeh <yaltayeh@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/13 02:19:13 by yaltayeh          #+#    #+#             */
<<<<<<< HEAD:src/execution/flow_control.c
/*   Updated: 2025/04/13 17:42:12 by yaltayeh         ###   ########.fr       */
=======
/*   Updated: 2025/04/13 23:09:04 by yaltayeh         ###   ########.fr       */
>>>>>>> refs/remotes/origin/linked_list:src/flow_control.c
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
<<<<<<< HEAD:src/execution/flow_control.c
			test = !pipeline_control(mini);
			if (op == 2)
				test = !test;	
=======
			mini->exit_status = pipeline_control(mini);
			test = !mini->exit_status;
			if (op == 2)
				test = !test;
>>>>>>> refs/remotes/origin/linked_list:src/flow_control.c
		}
		if (op == 0)
			break ;
		lst_move2next(&mini->tokens);
	}
	return (0);
}