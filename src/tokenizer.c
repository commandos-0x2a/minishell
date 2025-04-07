/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaltayeh <yaltayeh@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/17 12:19:29 by yaltayeh          #+#    #+#             */
/*   Updated: 2025/04/08 02:01:46 by yaltayeh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_list	*add_token(t_list **lst, char *token)
{
	t_list	*new;
	
	if (!token)
	{
		fclean_list(lst);
		return (NULL);
	}
	new = malloc(sizeof(t_list));
	if (!new)
	{
		free(token);
		fclean_list(lst);
		return (NULL);
	}
	new->next = *lst;
	new->token = token;
	*lst = new;
	return (new);
}

/*
* Let me explain what this function does:
* 
* Imagine you have a sentence like: "play with penguin in my room"
* This function is like a magical sentence splitter!
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
* where each piece has one word! 
*/

static t_list	*tokenizer_iter(t_list *lst, char *s, int i)
{
	char	*start;

	while (*s == ' ')
		s++;
	start = s;
	while (*s && *s != ' ')
	{
		if (*s == '\'' || *s == '\"')
		{
			s = ft_strchr(s + 1, *s);
			if (!s)
				break ;
		}
		s++;
	}
	if (s == NULL)
	{
		write(2, PREFIX"syntax error\n", sizeof(PREFIX"syntax error\n") - 1);
		return (fclean_list(&lst));
	}
	if (start == s && !*s)
		return (ft_calloc(1, sizeof(t_list)));
	lst = tokenizer_iter(lst, s + !!*s, i + 1);
	if (!lst)
		return (NULL);
	add_token(&lst, ft_substr(start, 0, s - start));
	if (!lst)
		return (NULL);
	return (lst);
}

t_list	*tokenizer(char *s)
{
	return (tokenizer_iter(NULL, s, 0));
}
