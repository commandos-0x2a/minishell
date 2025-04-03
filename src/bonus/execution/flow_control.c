/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flow_control.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaltayeh <yaltayeh@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/07 08:13:50 by yaltayeh          #+#    #+#             */
/*   Updated: 2025/04/03 20:26:51 by yaltayeh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	pipeline_check_syntax(char **tokens, char **tokens_brk);

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

int	flow_check_syntax(char **tokens)
{
	char	**next_pipeline;
	int		op;

	while (*tokens)
	{
		next_pipeline = get_next_pipeline(tokens, &op);
		if (op && *++next_pipeline == NULL)
		{
			ft_fprintf(2, PREFIX"syntax error in flow control\n");
			return (-1);
		}
		if (pipeline_check_syntax(tokens, next_pipeline) != 0)
			return (-1);
		tokens = next_pipeline;
	}
	return (0);
}

// allocate:
//	- char *line
//	- char	**env # global
int	flow_control(t_mdata *mdata)
{
	int			op;
	int			test;
	char		**pipeline;
	char		**next_pipeline;

	mdata->tokens = tokenizer(mdata->line);
	if (!mdata->tokens)
	{
		PRINT_ALLOCATE_ERROR;
		return (-1);
	}
	if (flow_check_syntax(mdata->tokens) == -1)
		return (-1);
	pipeline = mdata->tokens;
	test = 1; // cuz run first time
	while (*pipeline)
	{
		next_pipeline = get_next_pipeline(pipeline, &op);
		if (op)
			*next_pipeline++ = NULL; // set operation token NULL and skip it
		if (test)
			test = !pipeline_control(mdata, pipeline); // toggle cuz exec when success return (0)
		if (op == 2) // is op == OR toggle test
			test = !test;
		pipeline = next_pipeline;
	}
	if (mdata->tokens)
		free(mdata->tokens);
	return (0);
}
