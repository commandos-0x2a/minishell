/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaltayeh <yaltayeh@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/17 12:19:29 by yaltayeh          #+#    #+#             */
/*   Updated: 2025/04/16 17:21:12 by yaltayeh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_list	*add_token(t_list **lst, char *token)
{
	t_list	*new;
	
	if (!token)
	{
		lst_clean(lst);
		return (NULL);
	}
	new = malloc(sizeof(t_list));
	if (!new)
	{
		free(token);
		lst_clean(lst);
		return (NULL);
	}
	new->next = *lst;
	new->str = token;
	*lst = new;
	return (new);
}

static char	*cut_slice(char **s_r)
{
	char	*start;
	int		nb_bracket;
	char	*s;

	s = *s_r;
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
	*s_r = s;
	if (s == NULL || nb_bracket != 0)
		return (NULL);
	return (start);
}

static t_list	*tokenizer_iter(char *s, int i)
{
	char	*start;
	t_list	*lst;

	start = cut_slice(&s);
	if (!start || !s)
	{
		write(2, PREFIX"syntax error\n", sizeof(PREFIX"syntax error\n") - 1);
		return (NULL);
	}
	if (start == s && !*s)
		return (ft_calloc(1, sizeof(t_list)));
	lst = tokenizer_iter(s + !!*s, i + 1);
	if (!lst)
		return (NULL);
	add_token(&lst, ft_substr(start, 0, s - start));
	if (!lst)
		return (NULL);
	return (lst);
}

t_list	*tokenizer(char *s)
{
	char	*expand_str;
	t_list	*tokens;

	expand_str = add_space_to_line(s);
	if (!expand_str)
		return (NULL);
	tokens = tokenizer_iter(expand_str, 0);
	free(expand_str);
	return (tokens);
}
