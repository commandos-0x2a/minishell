/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_env.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaltayeh <yaltayeh@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/23 21:27:16 by yaltayeh          #+#    #+#             */
/*   Updated: 2025/04/25 01:33:38 by yaltayeh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
	else if (str[*i] == '\0' || str[*i] == ' '
		|| str[*i] == SINGLE_QUOTE || str[*i] == DOUBLE_QUOTE)
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
		if ((str[i] == SINGLE_QUOTE || str[i] == DOUBLE_QUOTE) && !quote_char)
			quote_char = str[i];
		else if (str[i] == quote_char)
			quote_char = 0;
		else if (str[i] == '$' && quote_char != SINGLE_QUOTE)
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
