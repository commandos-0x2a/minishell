/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_getenv.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkurkar <mkurkar@student.42amman.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/16 07:25:20 by yaltayeh          #+#    #+#             */
/*   Updated: 2025/01/11 16:36:52 by mkurkar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char ***__init__env(void)
{
	static char **g_env_copy;
	return (&g_env_copy);
}

char **create_env_copy(void)
{
	extern char **environ;
	char **new_env;
	int i;

	i = 0;
	while (environ[i])
		i++;
	new_env = (char **)malloc(sizeof(char *) * (i + 1));
	if (!new_env)
		return (NULL);
	i = 0;
	while (environ[i])
	{
		new_env[i] = ft_strdup(environ[i]);
		if (!new_env[i])
		{
			while (--i >= 0)
				free(new_env[i]);
			free(new_env);
			return (NULL);
		}
		i++;
	}
	new_env[i] = NULL;
	return (new_env);
}

char *ft_getenv(const char *name)
{
	size_t name_len;
	int i;
	char ***g_env_copy;
	g_env_copy = __init__env();

	if (!name)
		return (NULL);
	if (!(*g_env_copy))
	{
		(*g_env_copy) = create_env_copy();
		if (!(*g_env_copy))
			return (NULL);
	}
	name_len = ft_strlen(name);
	i = 0;
	while ((*g_env_copy)[i])
	{
		if (ft_strncmp((*g_env_copy)[i], name, name_len) == 0 &&
			(*g_env_copy)[i][name_len] == '=')
		{
			return (ft_strdup((*g_env_copy)[i] + name_len + 1));
		}
		i++;
	}
	return (NULL);
}

void cleanup_env_copy(void)
{
	int i;
	char ***g_env_copy;
	g_env_copy = __init__env();

	if ((*g_env_copy))
	{
		i = 0;
		while ((*g_env_copy)[i])
		{
			free((*g_env_copy)[i]);
			i++;
		}
		free((*g_env_copy));
		(*g_env_copy) = NULL;
	}
}
