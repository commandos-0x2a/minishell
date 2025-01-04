/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkurkar <mkurkar@student.42amman.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/17 12:19:29 by yaltayeh          #+#    #+#             */
/*   Updated: 2025/01/04 17:04:34 by mkurkar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**tokenizer(char *s, int i)
{
	char	*p;
	char	**tokens;
	int		nb_bracket;
	char    quote_char;

	while (*s == ' ')
		s++;
	p = s;
	nb_bracket = 0;
	quote_char = 0;
	while (*s)
	{
		if (!quote_char && (*s == '\'' || *s == '\"'))
			quote_char = *s;
		else if (quote_char && *s == quote_char)
			quote_char = 0;
		else if (!quote_char)
		{
			if (*s == '(')
				nb_bracket++;
			else if (*s == ')')
				nb_bracket--;
			else if (*s == ' ' && nb_bracket == 0)
				break;
		}
		s++;
	}
	if (nb_bracket != 0)
	{
		write(2, "syntax error\n", 13);
		return (NULL);
	}
	if (p == s && !*s)
		return (ft_calloc(i + 1, sizeof(char *)));
	tokens = tokenizer(s + (*s == ' ' ? 1 : 0), i + 1);
	if (!tokens)
		return (NULL);
	if (*s)
		*s = '\0';
	tokens[i] = p;
	return (tokens);
}
