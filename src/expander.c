/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaltayeh <yaltayeh@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/05 13:54:21 by yaltayeh          #+#    #+#             */
/*   Updated: 2025/01/05 21:56:40 by yaltayeh         ###   ########.fr       */
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


char	*str_expander(char *arg)
{
	char	*s;
	char	*tmp;
	size_t	i;
	char	*str;

	s = arg;
	i = 0;
	while (*s)
	{
		if (*s == '\'')
		{
			tmp = ft_strchr(++s, '\'');
			if (!tmp)
				return (NULL);
			i += tmp - s;
			s = tmp + 1;
			continue ;
		}
		i++;
		s++;
	}
	str = malloc((i + 1) * sizeof(char));
	if (!str)
		return (NULL);
	s = arg;
	while (*s)
	{

		/* code */
	}
	
	return (arg);
}

void	argv_expander_new(char **argv)
{
	int	i;

	i = 0;
	while (argv[i])
	{
		argv[i] = str_expander(argv[i]);
		i++;
	}
}
