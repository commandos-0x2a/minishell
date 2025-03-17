/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_tokenizer.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaltayeh <yaltayeh@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/07 16:00:58 by yaltayeh          #+#    #+#             */
/*   Updated: 2025/03/17 12:48:48 by yaltayeh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_bonus.h"

char	*expand_str_no_quote(char *str);

void	print_tokenizer(char *line, int indent)
{
	t_tokens tok;
	int		i;

	tok = tokenizer(line);
	free(line);
	if (!tok.tokens)
		return ;
	if (flow_check_syntax(tok.tokens) == -1)
	{
		free_tokens(&tok);
		return ;
	}
	i = 0;
	while (tok.tokens[i])
	{
		// if (tokens[i][0] == '(')
		// {
		// 	tokens[i][ft_strlen(tokens[i]) - 1] = '\0';
		// 	tokens[i]++;
		// 	print_tokenizer(tokens[i], indent + 4);
		// }
		// else
		printf("%-*s%i: %s\n", indent, "", i, tok.tokens[i]);
		i++;
	}
}
