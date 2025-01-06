/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaltayeh <yaltayeh@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/05 13:54:21 by yaltayeh          #+#    #+#             */
/*   Updated: 2025/01/07 00:15:31 by yaltayeh         ###   ########.fr       */
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

static char *expand_env_var(char *str, int *i)
{
    char *var_name;
    char *var_value;
    int start;
    int len;

    (*i)++;  // Skip the '$'
    if (str[*i] == '?')  // Handle $? for last exit status
    {
        (*i)++;
        return (ft_itoa(127, 1));
    }
    if (str[*i] == '\0' || str[*i] == ' ' || str[*i] == '\'' || str[*i] == '\"')
        return (ft_strdup("$"));

    // Handle numeric variables (like $1, $2, etc.)
    if (ft_isdigit(str[*i]))
    {
        (*i)++;
        return (ft_strdup(""));  // Return empty string for numeric vars
    }

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

    return (var_value ? ft_strdup(var_value) : ft_strdup(""));
}

static char *join_and_free(char *s1, char *s2)
{
    char *result;

    result = ft_strjoin(2, s1, s2);
    free(s1);
    free(s2);
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
void argv_expander(char **argv)
{
    char    *ptr;
    char    *result;
    char    *temp;
    char    quote_char;
    int     i;
    int     j;

    i = 0;
    while (argv[i])
    {
        ptr = argv[i];
        result = ft_strdup("");

        j = 0;
        quote_char = 0;
        while (ptr[j])
        {
			if (!result) // to detect all result malloc failed
				return;
            // Handle quotes
            if ((ptr[j] == '\'' || ptr[j] == '\"') && !quote_char)
            {
                quote_char = ptr[j++];
                continue;
            }
            if (ptr[j] == quote_char)
            {
                quote_char = 0;
                j++;
                continue;
            }

            // Handle environment variables
            if (ptr[j] == '$' && quote_char != '\'')
            {
                temp = expand_env_var(ptr, &j);
                if (temp)
                    result = join_and_free(result, temp);
                continue;
            }

            // Handle escape character
            if (ptr[j] == '\\' && (!quote_char || quote_char == '\"'))
            {
                if (ptr[j + 1])
                {
                    temp = ft_substr(ptr, j + 1, 1);
                    result = join_and_free(result, temp);
                    j += 2;
                }
                continue;
            }

            // Normal character
            temp = ft_substr(ptr, j, 1);
            result = join_and_free(result, temp);
            j++;
        }

        free(argv[i]);
        argv[i] = result;
        i++;
    }
}
