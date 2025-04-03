/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaltayeh <yaltayeh@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/17 12:19:29 by yaltayeh          #+#    #+#             */
/*   Updated: 2025/03/22 15:09:19 by yaltayeh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
* Let me explain what this function does:
* 
* Imagine you have a sentence like: "play with penguin in my room"
* This function is like a magical sentence splitter! 🪄
* 
* What it does:
* 1. It looks at your sentence
* 2. Cuts it into separate words (we call them tokens)
* 3. Makes sure special words in quotes stay together
* 4. Checks if brackets () are used correctly
* 
* For example:
* Input: play "with penguin"
* Output: ["play", "\"with penguin\""]
* 
* It's like taking a long piece of paper and cutting it into smaller pieces,
* where each piece has one word! ✂️
*/
static char	**tokenizer_iter(char *s, int i)
{
	char	*start;
	char	**tokens;
	int		nb_bracket;

	while (*s == ' ')
		s++;
	start = s;
	nb_bracket = 0;
	while (*s && (*s != ' ' || nb_bracket))
	{
		if (*s == '(')
			nb_bracket++;
		if (*s == ')')
			nb_bracket--;
		if (nb_bracket < 0)
			break ;
		if (*s == '\'' || *s == '\"')
		{
			s = ft_strchr(s + 1, *s);
			if (!s)
				break ;
		}
		s++;
	}
	if (nb_bracket != 0 || s == NULL)
	{
		write(2, PREFIX"syntax error\n", sizeof(PREFIX"syntax error\n") - 1);
		return (NULL);
	}
	if (start == s && !*s)
		return (ft_calloc(i + 1, sizeof(char *)));
	tokens = tokenizer_iter(s + !!*s, i + 1);
	if (!tokens)
		return (NULL);
	*s = '\0';
	tokens[i] = start;
	return (tokens);
}

char	**tokenizer(char *s)
{
	return (tokenizer_iter(s, 0));
}