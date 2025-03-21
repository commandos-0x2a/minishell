/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flow_control.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaltayeh <yaltayeh@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/07 08:13:50 by yaltayeh          #+#    #+#             */
/*   Updated: 2025/03/21 18:19:25 by yaltayeh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	pipeline_check_syntax(char **tokens, char **tokens_brk);

/**
 * flow is part from operation and next operation (&& or ||)
 * 
 * another way split line by operation
 * 
 * Example: 
 * > cmd1 && cmd2 | cmd3 || cmd4 > out
 * 
 * tokens:
 * 		0: cmd1
 * 		1: &&
 * 		2: cmd2
 * 		3: |
 * 		4: cmd3
 * 		5: ||
 * 		6: cmd4
 * 		7: >
 * 		8: out
 * flows:
 * 		0: [cmd1]			OP: AND
 * 		1: [cmd2, |, cmd3]	OP: OR
 * 		2: [cmd4, >, out]
 * 
*/

/*
static char	**get_next_pipeline(char **tokens, int *op)
{
	*op = 0;
	while (*tokens)
	{
		if (ft_strcmp(*tokens, "&&") == 0)
		{
			*op = 1;
			break ;
		}
		else if (ft_strcmp(*tokens, "||") == 0)
		{
			*op = 2;
			break ;
		}
		tokens++;
	}
	return (tokens);
}
*/

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

int	flow_control(char *line)
{
	int			op;
	int			test;
	char		**pipeline;
	char		**next_pipeline;
	char		**tokens;

	tokens = tokenizer(line);
	if (!tokens)
	{
		PRINT_ALLOCATE_ERROR;
		return (-1);
	}
	if (flow_check_syntax(tokens) == -1)
		return (-1);
	pipeline = tokens;
	test = 1; // cuz run first time
	while (*pipeline)
	{
		next_pipeline = get_next_pipeline(pipeline, &op);
		if (op)
		{
			free(*next_pipeline);
			*next_pipeline++ = NULL; // set operation token NULL and skip it
		}
		if (test)
		{
			test = !pipeline_control(pipeline); // toggle cuz exec when success return (0)
		}
		if (op == 2) // is op == OR toggle test
			test = !test;
		pipeline = next_pipeline;
	}
	return (0);
}
