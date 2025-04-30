/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_wildcard.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaltayeh <yaltayeh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/05 21:33:13 by mkurkar           #+#    #+#             */
/*   Updated: 2025/04/30 08:59:00 by yaltayeh         ###   ########.fr       */
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
* Imagine arranging your toys in alphabetical order! 
* This function is like organizing your toys from A to Z.
* Just like when you line up your stuffed animals:
* First comes Bear, then Cat, then Dog, then Elephant!
*/
static void	sort_strings(char **arr)
{
	char	*temp;
	int		i;
	int		j;

	i = 0;
	while (arr[i])
	{
		j = 0;
		while (arr[j + i] && arr[j + i + 1])
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
	return (ret);
}

char	**expand_wildcard_iter(char *pattern, DIR *dir, int i)
{
	struct dirent	*entry;
	int				is_match;
	char			**match_files;

	entry = readdir(dir);
	if (entry == NULL)
		return (ft_calloc(i, sizeof(char *)));
	if (entry->d_name[0] == '.' && pattern[0] != '.')
		is_match = 0;
	else
		is_match = match_pattern(pattern, entry->d_name, '\0');
	match_files = expand_wildcard_iter(pattern, dir, i + is_match);
	if (!match_files)
		return (NULL);
	if (is_match)
	{
		match_files[i] = ft_strdup(entry->d_name);
		if (!match_files[i])
		{
			free_dptr(match_files);
			return (NULL);
		}
	}
	return (match_files);
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
	char			**files;

	if (is_contain_wildcard(pattern) == 0)
		return (original_argument(pattern));
	dir = opendir(".");
	if (!dir)
		return (NULL);
	files = expand_wildcard_iter(pattern, dir, 0);
	closedir(dir);
	if (!files)
		return (NULL);
	if (!*files)
	{
		free(files);
		return (original_argument(pattern));
	}
	sort_strings(files);
	return (files);
}
