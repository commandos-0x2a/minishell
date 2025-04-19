/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_syntax.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkurkar <mkurkar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/03 20:44:58 by yaltayeh          #+#    #+#             */
/*   Updated: 2025/04/14 15:13:09 by mkurkar          ###   ########.fr       */
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

static int	check_redirection_syntax(t_list *lst)
{
	if (!lst->next || !lst->next->str)
	{
		ft_fprintf(2, PREFIX"syntax error near unexpected token `newline'\n");
		return (0);
	}
	if (operation_type(lst->next->str) != 0)
	{
		ft_fprintf(2, PREFIX"syntax error near unexpected token `%s'\n", 
			lst->next->str);
		return (0);
	}
	return (1);
}

static int	check_pipe_or_logical_syntax(t_list *lst, t_list *prev_tokens)
{
	if (!lst->next || !lst->next->str || !prev_tokens || !prev_tokens->str)
	{
		ft_fprintf(2, PREFIX"syntax error near unexpected token `%s'\n", lst->str);
		return (0);
	}
	if (ft_strcmp(lst->next->str, "|") == 0 || \
		ft_strcmp(lst->next->str, "||") == 0 || \
		ft_strcmp(lst->next->str, "&&") == 0)
	{
		ft_fprintf(2, PREFIX"syntax error near unexpected token `%s'\n", 
			lst->next->str);
		return (0);
	}
	return (1);
}

int	check_syntax(t_list *lst)
{
	t_list	*prev_tokens;
	int		op_type;

	prev_tokens = NULL;
	while (lst && lst->str)
	{
		op_type = operation_type(lst->str);
		if (op_type == 1)
		{
			if (!check_redirection_syntax(lst))
				return (0);
		}
		else if (op_type == 2)
		{
			if (!check_pipe_or_logical_syntax(lst, prev_tokens))
				return (0);
		}
		prev_tokens = lst;
		lst = lst->next;
	}
	return (1);
}
