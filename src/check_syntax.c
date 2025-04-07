/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_syntax.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaltayeh <yaltayeh@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/03 20:44:58 by yaltayeh          #+#    #+#             */
/*   Updated: 2025/04/07 18:59:08 by yaltayeh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	operation_type(char *str)
{
	if (ft_strcmp(str, ">>") == 0 || \
		ft_strcmp(str, ">") == 0 || \
		ft_strcmp(str, "<<") == 0 || \
		ft_strcmp(str, "<") == 0)
		return (1);
	else if (ft_strcmp(str, "|") == 0 || \
		ft_strcmp(str, "||") == 0 || \
		ft_strcmp(str, "&&") == 0)
		return (2);
	
	else
		return (0);
}


int check_syntax(t_list *lst)
{
	t_list	*prev_tokens;

	prev_tokens = NULL;
	while (lst && lst->token)
	{
		if (ft_strcmp(lst->token, ">>") == 0 || \
			ft_strcmp(lst->token, ">") == 0 || \
			ft_strcmp(lst->token, "<<") == 0 || \
			ft_strcmp(lst->token, "<") == 0)
		{
			if (!lst->next)
			{
				ft_fprintf(2, PREFIX"syntax error near unexpected token `newline'\n");
				return (0);
			}
			if (operation_type(lst->next->token) != 0)
			{
				ft_fprintf(2, PREFIX"syntax error near unexpected token `%s'\n", lst->next->token);
				return (0);
			}	
		}
		else if (ft_strcmp(lst->token, "|") == 0 || \
				ft_strcmp(lst->token, "||") == 0 || \
				ft_strcmp(lst->token, "&&") == 0)
		{
			if (!lst->next || !lst->next->token)
			{
				ft_fprintf(2, PREFIX"syntax error near unexpected token `%s'\n", lst->token);
				return (0);
			}
			if (!prev_tokens)
			{
				ft_fprintf(2, PREFIX"syntax error near unexpected token `%s'\n", lst->token);
				return (0);
			}
			if (ft_strcmp(lst->next->token, "|") == 0 || \
				ft_strcmp(lst->next->token, "||") == 0 || \
				ft_strcmp(lst->next->token, "&&") == 0)
			{
				ft_fprintf(2, PREFIX"syntax error near unexpected token `%s'\n", lst->next->token);
				return (0);
			}
		}
		if (!prev_tokens)
			prev_tokens = lst;
		lst = lst->next;
	}
    return (1);
}