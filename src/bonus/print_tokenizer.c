/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_tokenizer.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaltayeh <yaltayeh@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/07 16:00:58 by yaltayeh          #+#    #+#             */
/*   Updated: 2025/03/21 18:17:17 by yaltayeh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*expand_str_no_quote(char *str);

void	print_tokenizer(char *line, int indent)
{
	char	**tokens;
	int		i;

	tokens = tokenizer(line);
	if (!tokens)
		return ;
	if (flow_check_syntax(tokens) == -1)
	{
		return ;
	}
	i = 0;
	while (tokens[i])
	{
		// if (tokens[i][0] == '(')
		// {
		// 	tokens[i][ft_strlen(tokens[i]) - 1] = '\0';
		// 	tokens[i]++;
		// 	print_tokenizer(tokens[i], indent + 4);
		// }
		// else
		printf("%-*s%i: %s\n", indent, "", i, tokens[i]);
		i++;
	}
}
