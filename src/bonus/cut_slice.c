/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cut_slice.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaltayeh <yaltayeh@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/27 20:36:57 by yaltayeh          #+#    #+#             */
/*   Updated: 2025/04/27 21:18:02 by yaltayeh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>
#include <stdlib.h>

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
