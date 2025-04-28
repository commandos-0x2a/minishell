/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_wildcard.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaltayeh <yaltayeh@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/05 21:33:13 by mkurkar           #+#    #+#             */
/*   Updated: 2025/04/27 23:42:19 by yaltayeh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <dirent.h>

static int	is_contain_wildcard(char *pattern)
{
	int	qout;

	qout = '\0';
	while (*pattern)
	{
		if ((*pattern == SINGLE_QUOTE || *pattern == DOUBLE_QUOTE)
			&& (*pattern == qout || qout == '\0'))
		{
			if (qout)
				qout = '\0';
			else
				qout = *pattern;
		}
		else if (*pattern == '*' || *pattern == '?')
			return (1);
		pattern++;
	}
	return (0);
}

/*
 * This function is like playing a matching game!
 * It checks if a word matches a special pattern.
 * For example:
 * Pattern: "cat*" will match: "cat", "cats", "catfood"
 * Pattern: "?at" will match: "cat", "rat", "hat"
 * The * is like a magic star that matches anything!
 * The ? is like a surprise box that matches any letter!
 * example:
 * Pattern:	h e * o ?
 * String: 	h e l l o !
 * 		   	↓ ↓ ↓ ↓ ↓ ↓
 * Step 1: 	h = h ✓ (exact match)
 * Step 2: 	e = e ✓ (exact match)
 * Step 3: 	* matches 'l l' ✓ (asterisk can match multiple chars)
 * Step 4: 	o = o ✓ (exact match)
 * Step 5: 	? matches '!' ✓ (question mark matches any single char)
 * Result: MATCH ✓
 *
 * This function is like playing a matching game!
 * It checks if a word matches a special pattern.
 * For example:
 * Pattern: "cat*" will match: "cat", "cats", "catfood"
 * Pattern: "?at" will match: "cat", "rat", "hat"
 * The * is like a magic star that matches anything!
 * The ? is like a surprise box that matches any letter! 
 */
static int	match_pattern(const char *pattern, const char *str, char qout)
{
	while (*pattern && *str)
	{
		if ((*pattern == SINGLE_QUOTE || *pattern == DOUBLE_QUOTE)
			&& (*pattern == qout || qout == '\0'))
		{
			if (qout)
				qout = '\0';
			else
				qout = *pattern;
			pattern++;
			continue ;
		}
		else if (*pattern == '*' && qout == '\0')
		{
			while (*pattern == '*')
				pattern++;
			if (!*pattern)
				return (1);
			while (*str)
			{
				if (match_pattern(pattern, str, qout))
					return (1);
				str++;
			}
			return (match_pattern(pattern, str, qout));
		}
		else if (*pattern == '?' || *pattern == *str)
		{
			pattern++;
			str++;
			continue ;
		}
		return (0);
	}
	while (*pattern == '*')
		pattern++;
	return (*pattern == '\0' && *str == '\0');
}

/*
* This function is like adding a new toy to your toy box!
* It takes your old toy box (array) and makes a bigger one
* to fit one more toy (string) inside.
* Then it carefully moves all your old toys to the new box
* and adds the new toy at the end!
*/
static char	**add_to_array(char **arr, char *str, int *size)
{
	char	**new_arr;
	int		i;

	new_arr = malloc(sizeof(char *) * (*size + 2));
	if (!new_arr)
		return (NULL);
	i = 0;
	while (i < *size)
	{
		new_arr[i] = arr[i];
		i++;
	}
	new_arr[i] = ft_strdup(str);
	new_arr[i + 1] = NULL;
	*size += 1;
	free(arr);
	return (new_arr);
}

/*
* Imagine arranging your toys in alphabetical order! 
* This function is like organizing your toys from A to Z.
* Just like when you line up your stuffed animals:
* First comes Bear, then Cat, then Dog, then Elephant!
*/
static void	sort_strings(char **arr, int size)
{
	char	*temp;
	int		i;
	int		j;

	i = 0;
	while (i < size - 1)
	{
		j = 0;
		while (j < size - i - 1)
		{
			if (ft_strcmp(arr[j], arr[j + 1]) > 0)
			{
				temp = arr[j];
				arr[j] = arr[j + 1];
				arr[j + 1] = temp;
			}
			j++;
		}
		i++;
	}
}

static char	**original_argument(char *pattern)
{
	char	**ret;

	ret = ft_calloc(2, sizeof(char *));
	if (!ret)
		return (NULL);
	ret[0] = ft_strdup(pattern);
	if (!ret[0])
	{
		free(ret);
		return (NULL);
	}
	remove_qouts(ret[0]);
	return (ret);
}

/*
* This is like a treasure hunt in your room! 
* When you give it a pattern (like *.txt),
* it looks through all files in the folder
* and finds the ones that match your pattern!
* Just like finding all blue toys in your room!
*/
char	**expand_wildcard(char *pattern)
{
	DIR				*dir;
	struct dirent	*entry;
	char			**files;
	int				size;

	if (is_contain_wildcard(pattern) == 0)
		return (original_argument(pattern));
	dir = opendir(".");
	if (!dir)
		return (NULL);
	files = ft_calloc(1, sizeof(char *));
	if (!files)
	{
		closedir(dir);
		return (NULL);
	}
	size = 0;
	entry = readdir(dir);
	while (entry)
	{
		if (entry->d_name[0] == '.' && pattern[0] != '.')
			;
		else if (match_pattern(pattern, entry->d_name, '\0'))
		{
			files = add_to_array(files, entry->d_name, &size);
			if (!files)
			{
				closedir(dir);
				return (NULL);
			}
		}
		entry = readdir(dir);
	}
	closedir(dir);
	if (size > 0)
		sort_strings(files, size);
	if (size == 0)
	{
		free(files);
		return (original_argument(pattern));
	}
	return (files);
}
