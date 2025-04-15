/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   str_expander.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaltayeh <yaltayeh@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: Invalid date        by                   #+#    #+#             */
/*   Updated: 2025/04/14 22:26:15 by yaltayeh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <ctype.h>

static char *join_and_free(char *s1, char *s2)
{
    char *result;

    result = ft_strjoin(2, s1, s2);
    free(s1);
    free(s2);
    return (result);
}

static char *expand_env_var(t_mini *mini, char *str, int *i)
{
	char	*var_name;
	char	*var_value;
	int		start;
	int		len;

	// try to handle the $? case
	(*i)++;  // Skip the '$'
	// Handle $? special parameter
	if (str[*i] == '?')
	{
		(*i)++;
		return (ft_itoa(mini->exit_status, 0));
	}
	else if (str[*i] == '\0' || str[*i] == ' ' || str[*i] == '\'' || str[*i] == '\"')
		return (ft_strdup("$"));
	// Handle numeric variables (like $1, $2, etc.)
	else if (ft_isdigit(str[*i]))
	{
		(*i)++;
		return (ft_strdup("")); // Return empty string for numeric vars
	}
	else
	{
		start = *i;
		// Include numbers in variable names, but don't start with them
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

char	*expand_str(t_mini *mini, char *str)
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
		// Handle quotes
		if ((str[i] == '\'' || str[i] == '\"') && !quote_char)
		{
			quote_char = str[i++];
			continue;
		}
		if (str[i] == quote_char)
		{
			quote_char = 0;
			i++;
			continue;
		}

		// Handle environment variables
		if (str[i] == '$' && quote_char != '\'')
		{
			temp = expand_env_var(mini, str, &i);
			if (temp)
				result = join_and_free(result, temp);
			continue;
		}

		// Normal character
		result = join_and_free(result, ft_substr(str, i, 1));
		i++;
	}
	return (result);
}

char	**argv_expander(t_mini *mini, char **argv)
{
	int		i;
	int		len;
	char	**new_argv;

	i = 0;
	len = 0;
	while (argv[len])
		len++;
	new_argv = ft_calloc(len + 1, sizeof(char *));
	if (!new_argv)
		return (NULL);
	while (argv[i])
	{
		new_argv[i] = expand_str(mini, argv[i]);
		if (!new_argv[i])
		{
			free_dptr(new_argv);
			return (NULL);
		}
		i++;
	}
	return (new_argv);
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
		// Handle quotes
		if ((str[i] == '\'' || str[i] == '\"') && !quote_char)
			quote_char = str[i];
		else if (str[i] == quote_char)
			quote_char = 0;

		// Handle environment variables
		else if (str[i] == '$' && quote_char != '\'')
		{
			temp = expand_env_var(mini, str, &i);
			if (temp)
				result = join_and_free(result, temp);
			continue;
		}
		// Normal character
		temp = ft_substr(str, i, 1);
		result = join_and_free(result, temp);
		i++;
	}
	return (result);
}

char	*remove_qouts(char *str)
{
	char	*s1;
	char	*s2;
	char	*null_char;

	s1 = str;
	null_char = ft_strchr(str, '\0'); 
	while (*s1)
	{
		if (*s1 == '\'' || *s1 == '\"')
		{
			s2 = ft_strchr(s1 + 1, *s1);
			if (!s2)
				return (str);
			
			ft_memmove(s2, s2 + 1, null_char-- - s2);
			ft_memmove(s1, s1 + 1, null_char-- - s1);
			s1 = s2;
		}
		s1++;
	}
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
	tokens[i] = remove_qouts(token);
	return (tokens);
}

int	argv_expander2(t_mini *mini)
{
	char	*expanded_str;
	char	**slices;
	t_list	*lst;

	lst = mini->tokens;
	while (lst && lst->str)
	{
		expanded_str = expand_env(mini, lst->str);
		if (!expanded_str)
			return (1);
		slices = mini_tokonizer(expanded_str, 0);
		free(expanded_str);
		if (!slices)
			return (1);
		lst = lst_expand(lst, slices);
		free(slices);
		if (!lst)
			return (1);
		lst = lst->next;
	}
	return (0);
}
