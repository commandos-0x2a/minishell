/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_setenv.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaltayeh <yaltayeh@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/05 17:25:07 by mkurkar           #+#    #+#             */
/*   Updated: 2025/03/21 12:39:39 by yaltayeh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <string.h>

static int add_to_env(char ***env, char *string)
{
	int i = 0;
	char **new_environ;

	while ((*env)[i])
		i++;
	new_environ = malloc(sizeof(char *) * (i + 2));
	if (!new_environ)
		return (-1);
	i = 0;
	while ((*env)[i])
	{
		new_environ[i] = (*env)[i];
		i++;
	}
	new_environ[i] = ft_strdup(string);
	if (!new_environ[i])
	{
		free(new_environ);
		return (-1);
	}
	new_environ[i + 1] = NULL;
	free(*env);
	*env = new_environ;
	return (0);
}

static int ft_putenv(char *string)
{
	char ***g_env_copy;
	int i, len;
	char *eq;

	if (!string || !(eq = ft_strchr(string, '=')))
		return (-1);
	g_env_copy = __init__env();
	if (!(*g_env_copy))
		return (-1);

	len = eq - string;
	i = 0;
	while ((*g_env_copy)[i])
	{
		if (ft_strncmp((*g_env_copy)[i], string, len) == 0 && (*g_env_copy)[i][len] == '=')
		{
			char *dup = ft_strdup(string);
			if (!dup)
				return (-1);
			free((*g_env_copy)[i]);
			(*g_env_copy)[i] = dup;
			return (0);
		}
		i++;
	}
	return (add_to_env(g_env_copy, string));
}

int ft_setenv(const char *name, const char *value, int overwrite)
{
	char *current;
	char *new_var;
	char ***g_env_copy;

	if (!name || ft_strchr(name, '=') != NULL)
		return (-1);

	current = ft_getenv(name);
	if (current != NULL && !overwrite)
	{
		free(current);
		return (0);
	}

	if (!value)
	{
		g_env_copy = __init__env();
		int i = 0, j;
		size_t name_len = ft_strlen(name);

		while ((*g_env_copy)[i])
		{
			if (ft_strncmp((*g_env_copy)[i], name, name_len) == 0 &&
				(*g_env_copy)[i][name_len] == '=')
			{
				free((*g_env_copy)[i]);
				for (j = i; (*g_env_copy)[j]; j++)
					(*g_env_copy)[j] = (*g_env_copy)[j + 1];
				break;
			}
			i++;
		}
		free(current);
		return (0);
	}

	new_var = malloc(ft_strlen(name) + ft_strlen(value) + 2);
	if (!new_var)
		return (-1);

	strcpy(new_var, name);
	strcat(new_var, "=");
	strcat(new_var, value);

	int ret = ft_putenv(new_var);
	free(new_var);
	if (current)
		free(current);

	return (ret);
}
