/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_argv.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaltayeh <yaltayeh@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/09 19:32:20 by yaltayeh          #+#    #+#             */
/*   Updated: 2025/03/21 20:57:46 by yaltayeh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	swap_args(char **a, char **b)
{
	char	*tmp;

	tmp = *a;
	*a = *b;
	*b = tmp;
}

char	**get_argv(char **tokens)
{
	char	**argv;
	char	**last_argv;

	argv = NULL;
	while (*tokens)
	{
		if (ft_strcmp(*tokens, "<<") == 0 \
			|| ft_strcmp(*tokens, "<") == 0 \
			|| ft_strcmp(*tokens, ">>") == 0 \
			|| ft_strcmp(*tokens, ">") == 0)
		{
			*tokens = NULL;
			*++tokens = NULL;
		}
		else if (!argv)
		{
			argv = tokens;
			last_argv = tokens;
		}
		else
			swap_args(++last_argv, tokens);
		tokens++;
	}
	if (!argv)
		return (tokens);
	return (argv);
}
