/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flow_control.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaltayeh <yaltayeh@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/07 08:13:50 by yaltayeh          #+#    #+#             */
/*   Updated: 2025/01/10 12:19:17 by yaltayeh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * flow is part from operation and next operation (&& or ||)
 * 
 * another way split line by operation
 * 
 * Example: 
 * > cmd1 && cmd2 | cmd3 || cmd4 > out
 * flow[0] = cmd1
 * op: AND
 * flow[1] = cmd2 | cmd3
 * op: OR
 * flow[2] = cmd4 > out
*/
char	**get_next_flow(char **tokens, int *op)
{
	*op = 0;
	while (*tokens)
	{
		if (ft_strcmp(*tokens, "&&") == 0 
			|| ft_strcmp(*tokens, "||") == 0)
		{
			if (ft_strcmp(*tokens, "&&") == 0)
				*op = 1;
			else if (ft_strcmp(*tokens, "||") == 0)
				*op = 2;
			break ;
		}
		tokens++;
	}
	return (tokens);
}

int	flow_control(char *line)
{
	char	**tokens;
	char	**next_flow;
	int		op;
	char	**ptr;
	int		test;
	int		exit_status = 0;

	tokens = tokenizer(line, 0);
	if (!tokens)
		return (-1);

	ptr = tokens;
	ptr = tokens;
	test = 1; // cuz run first time
	while (*tokens)
	{
		next_flow = get_next_flow(tokens, &op);
		*next_flow = NULL; // replace operation token with NULL to end flow
		// if have operation check if have anything after it
		if (test)
		{
			exit_status = pipeline_control(tokens);
			if (exit_status == -1)
			{
				free(ptr);
				return (-1);
			}
			test = !exit_status; // toggle cuz exec when success return (0)
		}
		if (op && *++next_flow == NULL) // increment next_flow if operation exist to skip it
		{
			ft_fprintf(2, NAME": syntax erron in flow control\n");
			return (-1); // syntex error
		}
		if (op == 2) // is op == OR toggle test
			test = !test;

		if (next_flow != NULL)
			tokens = next_flow; 
		else
			break;
	}
	free(ptr);
	return (exit_status);
}
