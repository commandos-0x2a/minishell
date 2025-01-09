/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flow_control.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaltayeh <yaltayeh@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/07 08:13:50 by yaltayeh          #+#    #+#             */
/*   Updated: 2025/01/09 21:09:24 by yaltayeh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * Check if token is flow control operator
 */
int	is_flow_control_operator(char *token)
{
	return (ft_strcmp(token, "&&") == 0 || ft_strcmp(token, "||") == 0);
}

/**
 * Get next flow control operator
 */
char	**get_next_flow_control_operator(char **tokens, int *op)
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


/**
 * flow is part from operation and next operation (&& or ||)
 * 
 * another way split chain by operation
 * 
 * Example: 
 * > cmd1 && cmd2 | cmd3 || cmd4 > out
 * flow[0] = cmd1
 * op: AND
 * flow[1] = cmd2 | cmd3
 * op: OR
 * flow[2] = cmd4 > out
 */

int	flow_control(char *chain)
{
	char	**tokens;
	char	**next_flow;
	int		op;
	char	**ptr;
	int		test;

	if (chain == NULL)
		return (-1);
	tokens = tokenizer(chain, 0);
	if (!tokens)
		return (-1);

	ptr = tokens;
	test = 1; // cuz run first time
	while (*tokens)
	{
		next_flow = get_next_flow_control_operator(tokens, &op);
		*next_flow = NULL; // replace operation token with NULL to end flow
		// if have operation check if have anything after it
		if (test)
		{
			test = executioner(tokens);
			if (test == -1)
			{
				free(ptr);
				return (-1);
			}
			test = !test; // toggle cuz exec is success return (0)
		}
		if (op && *++next_flow == NULL) // increment next_flow if operation exist to skip it
		{
			ft_fprintf(2, NAME": syntax erron flow control\n");
			free(ptr);
			return (-1); // syntex error
		}
		if (op == 2) // If the operator is OR, toggle the test variable
			test = !test;

		if (next_flow != NULL)
			tokens = next_flow; 
		else
			break;
	}
	free(ptr);
	return (0);
}
