/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   match_pattern.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaltayeh <yaltayeh@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/05 21:33:13 by mkurkar           #+#    #+#             */
/*   Updated: 2025/04/29 00:08:22 by yaltayeh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	match_wildcard(const char *pattern, const char *str);

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
int	match_pattern(const char *pattern, const char *str, char qout)
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
			return (match_wildcard(pattern, str));
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

static int	match_wildcard(const char *pattern, const char *str)
{
	while (*pattern == '*')
		pattern++;
	if (!*pattern)
		return (1);
	while (*str)
	{
		if (match_pattern(pattern, str, '\0'))
			return (1);
		str++;
	}
	return (match_pattern(pattern, str, '\0'));
}
