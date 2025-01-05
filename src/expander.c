/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkurkar <mkurkar@student.42amman.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/05 13:54:21 by yaltayeh          #+#    #+#             */
/*   Updated: 2025/01/05 21:30:08 by mkurkar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	argv_expander(char **argv)
{
	int		i;
	size_t	len;

	i = 0;
	while (argv[i])
	{
		if (argv[i][0] == '\'' || argv[i][0] == '\"')
		{
			len = ft_strlen(argv[i]);
			if (len >= 2 && argv[i][len - 1] == argv[i][0])
			{
				argv[i][len - 1] = '\0';
				argv[i]++;
			}
		}
		i++;
	}
}


char	*str_expander(char *arg, int i)
{
	char	*s;
	char	*tmp;
	size_t	total_len;

	s = arg;
	total_len = 0;
	while (*s)
	{
		if (*s == '\'')
		{
			tmp = ft_strchr(++s, '\'');
			if (!tmp)
				return (NULL);
			total_len += tmp - s;
			s = tmp;
		}
		total_len++;
		s++;
	}
	(void)total_len; (void)i;
	return (arg);
}

void	argv_expander_new(char **argv)
{
	int	i;

	i = 0;
	while (argv[i])
	{
		argv[i] = str_expander(argv[i], 0);
		i++;
	}
}
