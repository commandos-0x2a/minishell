/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   str_expander.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaltayeh <yaltayeh@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: Invalid date        by                   #+#    #+#             */
/*   Updated: 2025/04/08 02:29:45 by yaltayeh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <ctype.h>

/**
 * 
 * Environment Variable Expansion System Map
 * =======================================
 * 
 * 1. argv_expander (Main Function)
 *    │
 *    ├── Purpose: Process command arguments and expand environment variables
 *    │   - Handles quoted strings
 *    │   - Processes environment variables
 *    │   - Manages escape characters
 *    │
 *    ├── Input: char **argv (array of command arguments)
 *    │   Example: ["echo", "$HOME", "\"$USER\"", '$PATH']
 *    │
 *    └── Process Flow:
 *        └── For each argument:
 *            ├── Initialize empty result string
 *            ├── Process character by character
 *            │   ├── Handle quotes ('" or '')
 *            │   ├── If '$' found → Call expand_env_var()
 *            │   ├── Handle escape characters
 *            │   └── Join results using join_and_free()
 *            └── Replace original argument with expanded version
 * 
 * 2. expand_env_var (Helper Function)
 *    │
 *    ├── Purpose: Extract and resolve environment variable values
 *    │   - Handles special case $?
 *    │   - Extracts variable names
 *    │   - Retrieves variable values
 *    │
 *    ├── Input: 
 *    │   - char *str (string containing env variable)
 *    │   - int *i (current position in string)
 *    │
 *    ├── Process:
 *    │   ├── Check for special case ($?)
 *    │   ├── Extract variable name
 *    │   └── Look up variable value
 *    │
 *    └── Output: Expanded value or empty string
 * 
 * 3. join_and_free (Utility Function)
 *    │
 *    ├── Purpose: Memory-safe string concatenation
 *    │   - Joins two strings
 *    │   - Frees original strings
 *    │   - Prevents memory leaks
 *    │
 *    ├── Input: 
 *    │   - char *s1 (first string)
 *    │   - char *s2 (second string)
 *    │
 *    └── Output: New concatenated string
 * 
 * Example Flow:
 * ------------
 * Input: echo "Welcome $USER to $HOME"
 * │
 * ├── argv_expander processes the argument
 * │   │
 * │   ├── Finds $USER
 * │   │   └── expand_env_var extracts "USER"
 * │   │       └── Returns "mkurkar"
 * │   │           └── join_and_free combines "Welcome " + "mkurkar"
 * │   │
 * │   └── Finds $HOME
 * │       └── expand_env_var extracts "HOME"
 * │           └── Returns "/home/mkurkar"
 * │               └── join_and_free combines previous result + " to " + "/home/mkurkar"
 * │
 * └── Final Output: "Welcome mkurkar to /home/mkurkar"
 */

// static int	get_env_var_name_len(char *str)
// {
// 	int	i;

// 	i = 0;
// 	while (str[i] && (ft_isalnum(str[i]) || str[i] == '_'))
// 		i++;
// 	return (i);
// }

static char *expand_env_var(char *str, int *i)
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
		return (strdup("WTF"));
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
		var_value = ft_getenv(var_name);
		free(var_name);
		if (!var_value)
			return (ft_strdup(""));
		return (var_value);
	}
}

static char *join_and_free(char *s1, char *s2)
{
    char *result;

    result = ft_strjoin(2, s1, s2);
    free(s1);
    free(s2);
    return (result);
}

char	*expand_str(char *str)
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
			temp = expand_env_var(str, &i);
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

char	*expand_str_no_quote(char *str)
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
			temp = expand_env_var(str, &i);
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

/*
* Enhanced version that handles:
* 1. Environment variables ($VAR, $PATH, etc.)
* 2. Quote removal and escaping
* 3. Special case $? for exit status
* 4. Preserves spaces in quotes
* 
* Examples:
* echo "$HOME/file"    -> /home/user/file
* echo '$HOME/file'    -> $HOME/file
* echo "Path: $PATH"   -> Path: /usr/bin:/bin
* echo $?             -> 0 (or last exit status)
*/
char	**argv_expander(char **argv)
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
		new_argv[i] = expand_str(argv[i]);
		if (!new_argv[i])
		{
			free_dptr(new_argv);
			return (NULL);
		}
		i++;
	}
	return (new_argv);
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

char	**argv_expander2(char **argv, int i)
{
	char	**new_argv;
	char	*expanded_str;
	char	**slices;
	int		j;

	if (!*argv)
		return (ft_calloc(i + 1, sizeof(char *)));
	
	expanded_str = expand_str_no_quote(*argv);
	if (!expanded_str)
		return (NULL);
	slices = mini_tokonizer(expanded_str, 0);
	free(expanded_str);
	if (!slices)
		return (NULL);
		
	j = 0;
	while (slices[j])
		j++;
	new_argv = argv_expander2(argv + 1, i + j);
	
	if (!new_argv)
	{
		free_dptr(slices);
		return (NULL);
	}
	j = 0;
	while (slices[j])
		new_argv[i++] = remove_qouts(slices[j++]);
	
	return (new_argv);
}
