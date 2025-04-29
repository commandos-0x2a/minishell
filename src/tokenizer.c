/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaltayeh <yaltayeh@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/17 12:19:29 by yaltayeh          #+#    #+#             */
/*   Updated: 2025/04/28 23:00:55 by yaltayeh         ###   ########.fr       */
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

static t_list	*tokenizer_iter(char *s, int i)
{
	char	*start;
	t_list	*lst;

	start = cut_slice(&s);
	if (!start || !s)
	{
		write(2, PREFIX"syntax error\n", sizeof(PREFIX"syntax error\n") - 1);
		return ((void *)0x1);
	}
	if (start == s && !*s)
		return (ft_calloc(1, sizeof(t_list)));
	lst = tokenizer_iter(s + !!*s, i + 1);
	if (!lst || lst == (void *)0x1)
		return (lst);
	add_token(&lst, ft_substr(start, 0, s - start));
	if (!lst)
		return (NULL);
	return (lst);
}

t_list	*tokenizer(const char *s)
{
	char	*expand_str;
	t_list	*tokens;

	expand_str = expand_line(s);
	if (!expand_str)
	{
		print_error(__FILE__, __LINE__);
		return (NULL);
	}
	tokens = tokenizer_iter(expand_str, 0);
	free(expand_str);
	return (tokens);
}
