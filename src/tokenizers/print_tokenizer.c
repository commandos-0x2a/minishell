/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_tokenizer.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaltayeh <yaltayeh@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/07 16:00:58 by yaltayeh          #+#    #+#             */
/*   Updated: 2025/02/08 17:29:08 by yaltayeh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_tokenizer(char *line, int indent)
{
	t_tokens	tok;
	int		i;

	tok = tokenizer(line);
	if (!tok.tokens)
		return ;
	i = 0;
	while (tok.tokens[i])
	{
		if (tok.tokens[i][0] == '(')
		{
			tok.tokens[i][ft_strlen(tok.tokens[i]) - 1] = '\0';
			tok.tokens[i]++;
			print_tokenizer(tok.tokens[i], indent + 4);
		}
		else
			printf("%-*s%i: %s\n", indent, "", i, tok.tokens[i]);
		i++;
	}
}
