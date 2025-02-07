/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flow_control.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaltayeh <yaltayeh@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/07 08:13:50 by yaltayeh          #+#    #+#             */
/*   Updated: 2025/02/07 15:32:41 by yaltayeh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	pipeline_check_syntax(char **tokens);

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
 * 		0: cmd1			OP: AND
 * 		1: cmd2 | cmd3	OP: OR
 * 		2: cmd4 > out
 * 
*/
static char	**get_next_command(char **tokens, int *op)
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

int	flow_check_syntax(char **tokens)
{
	char	**next_pipeline;
	int		op;
	
	while (*tokens)
	{
		next_pipeline = get_next_command(tokens, &op);
		if (op && *++next_pipeline == NULL)
		{
			ft_fprintf(2, NAME": syntax error in flow control\n");
			return (-1);
		}
		if (pipeline_check_syntax(tokens) != 0)
			return (-1);
		tokens = next_pipeline;
	}
	return (0);
}

int	flow_control(char *line)
{
	char	**tokens;
	char	**next_pipeline;
	int		op;
	char	**pipeline;
	int		test;
	int		exit_status = 0;

	tokens = tokenizer(line, 0);
	if (!tokens)
		return (-1);
	if (flow_check_syntax(tokens) == -1)
	{
		// free tokens
		return (-1);
	}
	pipeline = tokens;
	test = 1; // cuz run first time
	while (*pipeline)
	{
		next_pipeline = get_next_command(pipeline, &op);
		if (op)
			*next_pipeline++ = NULL; // set operation token NULL and skip it
		// if have operation check if have anything after it
		if (test)
		{
			exit_status = pipeline_control(pipeline);
			if (exit_status == -1)
			{
				// free tokens
				return (-1);
			}
			test = !exit_status; // toggle cuz exec when success return (0)
		}
		if (op == 2) // is op == OR toggle test
			test = !test;
		pipeline = next_pipeline;
	}
	// free tokens
	return (exit_status);
}
