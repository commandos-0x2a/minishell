/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaltayeh <yaltayeh@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/28 23:03:56 by yaltayeh          #+#    #+#             */
/*   Updated: 2025/04/28 23:05:10 by yaltayeh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

int	operation_type(char *str)
{
	if (ft_strcmp(str, ">>") == 0
		|| ft_strcmp(str, ">") == 0
		|| ft_strcmp(str, "<<") == 0
		|| ft_strcmp(str, "<") == 0)
		return (1);
	else if (ft_strcmp(str, "|") == 0
		|| ft_strcmp(str, "||") == 0
		|| ft_strcmp(str, "&&") == 0)
		return (2);
	else
		return (0);
}

size_t	operation_len(const char *s)
{
	if (ft_strncmp(s, "&&", 2) == 0 || ft_strncmp(s, "||", 2) == 0
		|| ft_strncmp(s, ">>", 2) == 0 || ft_strncmp(s, "<<", 2) == 0)
		return (2);
	else if (*s == '|' || *s == '<' || *s == '>')
		return (1);
	return (0);
}

char	*cut_slice(char **s_r)
{
	char	*start;
	int		nb_bracket;
	char	*s;

	s = *s_r;
	while (*s == ' ')
		s++;
	start = s;
	nb_bracket = 0;
	while (s && *s && (*s != ' ' || nb_bracket) && nb_bracket >= 0)
	{
		if (*s == '(')
			nb_bracket++;
		else if (*s == ')')
			nb_bracket--;
		else if (*s == '\'' || *s == '\"')
			s = ft_strchr(s + 1, *s);
		if (s)
			s++;
	}
	*s_r = s;
	if (s == NULL || nb_bracket != 0)
		return (NULL);
	return (start);
}
