/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_env.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaltayeh <yaltayeh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/23 21:27:16 by yaltayeh          #+#    #+#             */
/*   Updated: 2025/05/25 17:32:08 by yaltayeh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*join_and_free(char *s1, char *s2)
{
	char	*result;

	if (!s1 || !s2)
	{
		free(s1);
		free(s2);
		return (NULL);
	}
	result = ft_strjoin(2, s1, s2);
	free(s1);
	free(s2);
	return (result);
}

static char	*get_env_value(t_mini *mini, char *str, int *i)
{
	int		start;
	char	*var_name;
	char	*var_value;

	start = *i;
	while (str[*i] && (ft_isalnum(str[*i]) || str[*i] == '_'))
		(*i)++;
	if (*i == start)
		return (ft_strdup("$"));
	var_name = ft_substr(str, start, *i - start);
	if (!var_name)
		return (NULL);
	var_value = ft_getenv(mini->env, var_name);
	free(var_name);
	if (!var_value && errno != ENOMEM)
		return (ft_strdup(""));
	return (var_value);
}

static char	*expand_env_var(t_mini *mini, char *str, int *i)
{
	int	arg;

	(*i)++;
	if (str[*i] == '?')
	{
		(*i)++;
		if (g_sig != 0)
			mini->exit_status = 128 + g_sig;
		return (ft_itoa(mini->exit_status, 0));
	}
	else if (str[*i] == '\0' || str[*i] == ' ')
		return (ft_strdup("$"));
	else if (str[*i] == SINGLE_QUOTE || str[*i] == DOUBLE_QUOTE)
		return (ft_strdup(""));
	else if (ft_isdigit(str[*i]))
	{
		arg = str[*i] - '0';
		(*i)++;
		if (arg < mini->argc)
			return (ft_strdup(mini->argv[arg]));
		return (ft_strdup(""));
	}
	else
		return (get_env_value(mini, str, i));
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
			result = join_and_free(result, temp);
			continue ;
		}
		temp = ft_substr(str, i, 1);
		result = join_and_free(result, temp);
		i++;
	}
	return (result);
}
