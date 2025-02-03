/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaltayeh <yaltayeh@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/17 12:19:29 by yaltayeh          #+#    #+#             */
/*   Updated: 2025/02/03 20:32:00 by yaltayeh         ###   ########.fr       */
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
char	**tokenizer(char *s, int i)
{
	char	*p;
	char	**tokens;
	int		nb_bracket;

	while (*s == ' ')
		s++;
	p = s;
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
		if ((*s == '|' || ft_strncmp(s, "&&", 2) == 0) && nb_bracket == 0)
			break ;
		s++;
	}
	if (nb_bracket != 0 || s == NULL)
	{
		write(2, NAME": syntax error\n", sizeof(NAME": syntax error\n") - 1);
		return (NULL);
	}
	if (p == s && !*s)
		return (ft_calloc(i + 1, sizeof(char *)));
	if (ft_strncmp(p, "&&", 2) == 0 || ft_strncmp(p, "||", 2) == 0)
		s += 2;
	else if (*p == '|')
		s++;
	if (!*s \
		|| *s == '|' || ft_strncmp(s, "&&", 2) == 0 || ft_strncmp(s, "||", 2) == 0 \
		|| *p == '|' || ft_strncmp(p, "&&", 2) == 0 || ft_strncmp(p, "||", 2) == 0)
		tokens = tokenizer(s, i + 1);
	else
		tokens = tokenizer(s + 1, i + 1);

	if (!tokens)
		return (NULL);
	p = ft_substr(p, 0, s - p);
	if (!p)
	{
		free(tokens);
		return (NULL);
	}
	tokens[i] = p;
	return (tokens);
}
