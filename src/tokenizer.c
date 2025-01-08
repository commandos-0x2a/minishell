/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaltayeh <yaltayeh@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/17 12:19:29 by yaltayeh          #+#    #+#             */
/*   Updated: 2025/01/07 20:26:13 by yaltayeh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "minishell.h"

/*
* Let me explain what this function does:
* 
* Imagine you have a sentence like: "play with toys in my room"
* This function is like a magical sentence splitter! 🪄
* 
* What it does:
* 1. It looks at your sentence
* 2. Cuts it into separate words (we call them tokens)
* 3. Makes sure special words in quotes stay together
* 4. Checks if brackets () are used correctly
* 
* For example:
* Input: play "with toys"
* Output: ["play", "\"with toy\""]
* 
* It's like taking a long piece of paper and cutting it into smaller pieces,
* where each piece has one word! ✂️
*/

static int count_brackets(char *str)
{
    int count;
    int in_quotes;
    char quote_char;

    count = 0;
    in_quotes = 0;
    while (*str)
    {
		if ((*str == '\'' || *str == '\"') && !in_quotes)
		{
			in_quotes = 1;
			quote_char = *str;
		}
		else if (in_quotes && *str == quote_char)
			in_quotes = 0;
		else if (!in_quotes)
		{
			if (*str == '(')
				count++;
			else if (*str == ')')
				count--;
			if (count < 0)
				return (-1);
		}
		str++;
	}
	return count;
}

char	**tokenizer(char *s, int i)
{
	char	*p;
	char	**tokens;
	int		nb_bracket;

	while (*s == ' ')
		s++;
	p = s;
	nb_bracket = 0;

    // Add this check before processing
    if (count_brackets(s) != 0)
    {
        write(2, NAME": syntax error: unmatched parentheses\n", 35);
        return (NULL);
    }

	while (*s && (*s != ' ' || nb_bracket))
	{
		if (*s == '(')
			nb_bracket++;
		if (*s == ')')
			nb_bracket--;
		if (nb_bracket < 0)
			break;
		if (*s == '\'' || *s == '\"')
		{
			s = ft_strchr(s + 1, *s);
			if (!s)
				break;;
		}
		s++;
	}
	if (nb_bracket != 0 || s == NULL)
	{
		write(2, NAME": syntax error\n", 13);
		return (NULL);
	}
	if (p == s && !*s)
		return (ft_calloc(i + 1, sizeof(char *)));
	tokens = tokenizer(s + !!*s, i + 1);
	if (!tokens)
		return (NULL);
	*s = '\0';
	tokens[i] = p;
	return (tokens);
}
