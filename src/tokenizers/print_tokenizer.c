/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_tokenizer.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaltayeh <yaltayeh@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/07 16:00:58 by yaltayeh          #+#    #+#             */
/*   Updated: 2025/02/07 16:01:10 by yaltayeh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*expand_str_no_quote(char *str);

void	print_tokenizer(char *line, int indent)
{
	char	**tokens;
	char	*str;
	int		i;

	tokens = tokenizer(line, 0);
	if (!tokens)
		return ;
	i = 0;
	while (tokens[i])
	{
		str = expand_str_no_quote(tokens[i]);

		// if (tokens[i][0] == '(')
		// {
		// 	tokens[i][ft_strlen(tokens[i]) - 1] = '\0';
		// 	tokens[i]++;
		// 	print_tokenizer(tokens[i], indent + 4);
		// }
		// else
		printf("%-*s%i: %s\n", indent, "", i, str);
		free(str);
		i++;
	}
}
