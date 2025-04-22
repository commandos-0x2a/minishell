/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaltayeh <yaltayeh@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/21 14:16:31 by yaltayeh          #+#    #+#             */
/*   Updated: 2025/04/21 14:18:51 by yaltayeh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <ctype.h>

static char	*join_and_free(char *s1, char *s2)
{
	char	*result;

	result = ft_strjoin(2, s1, s2);
	free(s1);
	free(s2);
	return (result);
}

static char	*expand_env_var(t_mini *mini, char *str, int *i)
{
	char	*var_name;
	char	*var_value;
	int		start;
	int		len;

	(*i)++;
	if (str[*i] == '?')
	{
		(*i)++;
		return (ft_itoa(mini->exit_status, 0));
	}
	else if (str[*i] == '\0' || str[*i] == ' ' \
		|| str[*i] == '\'' || str[*i] == '\"')
		return (ft_strdup("$"));
	else if (ft_isdigit(str[*i]))
	{
		(*i)++;
		return (ft_strdup(""));
	}
	else
	{
		start = *i;
		while (str[*i] && (ft_isalnum(str[*i]) || str[*i] == '_'))
			(*i)++;
		len = *i - start;
		if (len == 0)
			return (ft_strdup("$"));
		var_name = ft_substr(str, start, len);
		if (!var_name)
			return (NULL);
		var_value = ft_getenv(mini->env, var_name);
		free(var_name);
		if (!var_value)
			return (ft_strdup(""));
		return (var_value);
	}
}

char	*expand_env(t_mini *mini, char *str)
{
	char	*result;
	char	*temp;
	char	quote_char;
	int		i;

	result = ft_strdup("");
	quote_char = 0;
	i = 0;
	while (str[i] && result)
	{
		if ((str[i] == '\'' || str[i] == '\"') && !quote_char)
			quote_char = str[i];
		else if (str[i] == quote_char)
			quote_char = 0;
		else if (str[i] == '$' && quote_char != '\'')
		{
			temp = expand_env_var(mini, str, &i);
			if (temp)
				result = join_and_free(result, temp);
			continue ;
		}
		temp = ft_substr(str, i, 1);
		result = join_and_free(result, temp);
		i++;
	}
	return (result);
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
		if ((*src == '\'' || *src == '\"') \
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

static char	**mini_tokonizer(char *s, int i)
{
	char	*start;
	char	**tokens;
	char	*token;

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
	if (start == s && !*s)
		return (ft_calloc(i + 1, sizeof(char *)));
	token = ft_substr(start, 0, s - start);
	if (!token)
		return (NULL);
	tokens = mini_tokonizer(s + !!*s, i + 1);
	if (!tokens)
	{
		free(token);
		return (NULL);
	}
	tokens[i] = token;
	return (tokens);
}

char	**expand_str(t_mini *mini, char *str)
{
	char	*expanded_str;
	char	**slices;

	expanded_str = expand_env(mini, str);
	if (!expanded_str)
		return (NULL);
	slices = mini_tokonizer(expanded_str, 0);
	free(expanded_str);
	return (slices);
}

int	expand_tokens(t_mini *mini, t_list *lst)
{
	char	**slices;
	t_list	*end;

	while (lst && lst->str)
	{
		slices = expand_str(mini, lst->str);
		if (!slices)
			return (-1);
		end = lst_expand(lst, slices);
		free(slices);
		if (!end)
			return (-1);
		end = end->next;
		while (lst && lst->str && lst != end)
		{
			slices = expand_wildcard(lst->str);
			if (!slices)
				return (-1);
			lst = lst_expand(lst, slices);
			free(slices);
			if (!lst)
				return (-1);
			lst = lst->next;
		}
	}
	return (0);
}

t_list	*expand_tokens_2lst(t_mini *mini, const char *str)
{
	t_list	*lst;

	lst = ft_calloc(1, sizeof(*lst));
	if (!lst)
		return (NULL);
	lst->str = ft_strdup(str);
	if (!lst->str)
	{
		lst_clean(&lst);
		return (NULL);
	}
	if (expand_tokens(mini, lst) != 0)
	{
		lst_clean(&lst);
		return (NULL);
	}
	return (lst);
}
