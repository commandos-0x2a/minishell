/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flow_control.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaltayeh <yaltayeh@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/07 08:13:50 by yaltayeh          #+#    #+#             */
/*   Updated: 2025/04/03 23:23:30 by yaltayeh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	get_operation_type(char *op_str)
{
	if (!op_str)
		return (0);
	if (ft_strcmp(op_str, "&&") == 0)
		return (1);
	else if (ft_strcmp(op_str, "||") == 0)
		return (2);
	return (0);
}

static char	**get_next_pipeline(char **tokens, int *op)
{
	char	**next;

	next = ft_tokpbrk(tokens, "&&", "||", NULL);
	*op = get_operation_type(*next);
	return (next);
}

int	flow_control(t_mdata *mdata)
{
	int			op;
	int			test;
	char		**pipeline;
	char		**next_pipeline;

	pipeline = mdata->tokens;
	test = 1;
	while (*pipeline)
	{
		next_pipeline = get_next_pipeline(pipeline, &op);
		if (op)
			*next_pipeline++ = NULL;
		if (test)
			test = !pipeline_control(mdata, pipeline);
		if (op == 2)
			test = !test;
		pipeline = next_pipeline;
	}
	return (0);
}
