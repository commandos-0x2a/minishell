/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flow_control.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaltayeh <yaltayeh@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/07 08:13:50 by yaltayeh          #+#    #+#             */
/*   Updated: 2025/01/10 01:05:15 by yaltayeh         ###   ########.fr       */
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
		if (is_flow_control_operator(*tokens))
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
	char	**ptr;
	int		test;

	tokens = tokenizer(line, 0);
	if (!tokens)
		return (-1);

	ptr = tokens;
	ptr = tokens;
	test = 1; // cuz run first time
	while (*tokens)
	{
		next_flow = get_next_flow_control_operator(tokens, &op);
		*next_flow = NULL; // replace operation token with NULL to end flow
		// if have operation check if have anything after it
		if (test)
		{
			test = pipeline_control(tokens);
			if (test == -1)
			{
				free(ptr);
				return (-1);
			test = !test; // toggle cuz exec when success return (0)
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
	free(ptr);
	return (0);
}
