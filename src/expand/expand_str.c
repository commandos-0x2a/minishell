/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_str.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaltayeh <yaltayeh@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/23 21:28:44 by yaltayeh          #+#    #+#             */
/*   Updated: 2025/05/26 15:14:34 by yaltayeh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	**ft_split(char *s, int i)
{
	char	*start;
	char	**tokens;
	char	*token;

	while (*s == ' ')
		s++;
	start = s;
	while (*s && *s != ' ')
	{
		if (*s == SINGLE_QUOTE || *s == DOUBLE_QUOTE)
			s = ft_strchr(s + 1, *s);
		s++;
	}
	if (start == s && !*s)
		return (ft_calloc(i + 1, sizeof(char *)));
	token = ft_substr(start, 0, s - start);
	if (!token)
		return (NULL);
	tokens = ft_split(s + !!*s, i + 1);
	if (tokens)
		tokens[i] = token;
	else
		free(token);
	return (tokens);
}

void	replace_qouts(char *s)
{
	char	*next;

	while (*s)
	{
		if (*s == '\'' || *s == '\"')
		{
			next = ft_strchr(s + 1, *s);
			if (!next)
				break ;
			if (*s == '\'')
			{
				*s = SINGLE_QUOTE;
				*next = SINGLE_QUOTE;
			}
			else if (*s == '\"')
			{
				*s = DOUBLE_QUOTE;
				*next = DOUBLE_QUOTE;
			}
			s = next;
		}
		s++;
	}
}

char	*remove_qouts(char *str)
{
	char	*src;
	char	*dst;
	char	qout;

	dst = str;
	src = str;
	qout = '\0';
	while (*src)
	{
		if ((*src == SINGLE_QUOTE || *src == DOUBLE_QUOTE)
			&& (qout == *src || qout == '\0'))
		{
			if (!qout)
				qout = *src;
			else
				qout = '\0';
			src++;
		}
		else
			*dst++ = *src++;
	}
	*dst = '\0';
	return (str);
}

char	**expand_str(t_mini *mini, char *str)
{
	char	*expanded_str;
	char	**slices;

	replace_qouts(str);
	expanded_str = expand_env(mini, str);
	if (!expanded_str)
		return (NULL);
	slices = ft_split(expanded_str, 0);
	if (slices && !*slices)
	{
		free(slices);
		slices = ft_calloc(2, sizeof(char *));
		if (slices)
			*slices = expanded_str;
		return (slices);
	}
	free(expanded_str);
	return (slices);
}
