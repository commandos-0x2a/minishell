/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_getenv.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkurkar <mkurkar@student.42amman.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/16 07:25:20 by yaltayeh          #+#    #+#             */
/*   Updated: 2025/01/04 16:34:07 by mkurkar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_getenv(const char *name)
{
	extern char	**environ;
	size_t		i;
	size_t		name_len;

	if (!name)
		return (NULL);
	i = 0;
	name_len = ft_strlen(name);
	while (environ[i])
	{
		if (ft_strncmp(environ[i], name, name_len) == 0)
		{
			if (environ[i][name_len] == '=')
				return (ft_strdup(environ[i] + name_len + 1));
		}
		i++;
	}
	return (NULL);
}
