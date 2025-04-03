/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_syntax.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaltayeh <yaltayeh@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/03 20:44:58 by yaltayeh          #+#    #+#             */
/*   Updated: 2025/04/03 21:22:30 by yaltayeh         ###   ########.fr       */
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


int check_syntax(char **tokens)
{
	char	**prev_tokens;

	prev_tokens = NULL;
	while (*tokens)
	{
		if (ft_strcmp(*tokens, ">>") == 0 || \
			ft_strcmp(*tokens, ">") == 0 || \
			ft_strcmp(*tokens, "<<") == 0 || \
			ft_strcmp(*tokens, "<") == 0)
		{
			if (!*(tokens + 1))
			{
				ft_fprintf(2, PREFIX"syntax error near unexpected token `newline'\n");
				return (0);
			}
			if (operation_type(*(tokens + 1)) != 0)
			{
				ft_fprintf(2, PREFIX"syntax error near unexpected token `%s'\n", *(tokens + 1));
				return (0);
			}	
		}
		else if (ft_strcmp(*tokens, "|") == 0 || \
				ft_strcmp(*tokens, "||") == 0 || \
				ft_strcmp(*tokens, "&&") == 0)
		{
			if (!*(tokens + 1))
			{
				ft_fprintf(2, PREFIX"syntax error near unexpected token `%s'\n", *tokens);
				return (0);
			}
			if (!prev_tokens)
			{
				ft_fprintf(2, PREFIX"syntax error near unexpected token `%s'\n", *tokens);
				return (0);
			}
			if (ft_strcmp(*(tokens + 1), "|") == 0 || \
				ft_strcmp(*(tokens + 1), "||") == 0 || \
				ft_strcmp(*(tokens + 1), "&&") == 0)
			{
				ft_fprintf(2, PREFIX"syntax error near unexpected token `%s'\n", *(tokens + 1));
				return (0);
			}
		}
		if (!prev_tokens)
			prev_tokens = tokens;
		tokens++;
	}
    return (1);
}