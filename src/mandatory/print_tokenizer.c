/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_tokenizer.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaltayeh <yaltayeh@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/07 16:00:58 by yaltayeh          #+#    #+#             */
/*   Updated: 2025/03/17 12:41:19 by yaltayeh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*expand_str_no_quote(char *str);

void	print_tokenizer(char *line, int indent)
{
	t_tokens tok;
	int		i;

	tok = tokenizer(line);
	free(line);
	if (!tok.tokens)
		return ;
	i = 0;
	while (tok.tokens[i])
	{
		printf("%-*s%i: %s\n", indent, "", i, tok.tokens[i]);
		i++;
	}
}
