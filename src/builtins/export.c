/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkurkar <mkurkar@student.42amman.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/11 12:00:00 by mkurkar           #+#    #+#             */
/*   Updated: 2025/01/11 16:37:01 by mkurkar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char *ft_strdup_env(const char *s)
{
	char *dup;
	int len;

	len = 0;
	while (s[len])
		len++;
	dup = malloc(len + 1);
	if (!dup)
		return (NULL);
	len = 0;
	while (s[len])
	{
		dup[len] = s[len];
		len++;
	}
	dup[len] = '\0';
	return (dup);
}

static int is_valid_identifier(char *str)
{
	if (!str || !*str || (*str >= '0' && *str <= '9'))
		return (0);
	while (*str && *str != '=')
	{
		if (!(((*str >= 'a') && (*str <= 'z')) ||
			  ((*str >= 'A') && (*str <= 'Z')) ||
			  ((*str >= '0') && (*str <= '9')) ||
			  *str == '_'))
			return (0);
		str++;
	}
	return (1);
}

static int update_env_var(char *var)
{
	char ***g_env_copy = __init__env();
	int i;
	char *name;
	char *equals;
	int name_len;

	equals = ft_strchr(var, '=');
	if (!equals)
		return (0);

	name_len = equals - var;
	name = malloc(name_len + 1);
	if (!name)
		return (1);
	strncpy(name, var, name_len);
	name[name_len] = '\0';

	i = 0;
	while ((*g_env_copy)[i])
	{
		if (ft_strncmp((*g_env_copy)[i], name, name_len) == 0 &&
			((*g_env_copy)[i][name_len] == '=' || (*g_env_copy)[i][name_len] == '\0'))
		{
			free((*g_env_copy)[i]);
			(*g_env_copy)[i] = ft_strdup(var);
			free(name);
			return ((*g_env_copy)[i] ? 0 : 1);
		}
		i++;
	}
	free(name);
	return (2); // Variable not found
}

static int add_env_var(char *var)
{
	char ***g_env_copy = __init__env();
	char **new_environ;
	int i, result;

	if (!(*g_env_copy))
	{
		*g_env_copy = create_env_copy();
		if (!(*g_env_copy))
			return (1);
	}

	result = update_env_var(var);
	if (result != 2)
		return (result);

	i = 0;
	while ((*g_env_copy)[i])
		i++;
	new_environ = malloc(sizeof(char *) * (i + 2));
	if (!new_environ)
		return (1);

	i = 0;
	while ((*g_env_copy)[i])
	{
		new_environ[i] = (*g_env_copy)[i];
		i++;
	}
	new_environ[i] = ft_strdup(var);
	if (!new_environ[i])
	{
		free(new_environ);
		return (1);
	}
	new_environ[i + 1] = NULL;
	free(*g_env_copy);
	*g_env_copy = new_environ;
	return (0);
}

static int is_critical_var(const char *var)
{
	const char *critical[] = {"PATH", "HOME", "USER", "SHELL", NULL};
	int i, len;

	i = 0;
	while (critical[i])
	{
		len = strlen(critical[i]);
		if (strncmp(var, critical[i], len) == 0 &&
			(var[len] == '=' || var[len] == '\0'))
			return (1);
		i++;
	}
	return (0);
}

int ft_export(char **argv)
{
	char ***g_env_copy = __init__env();
	int i;
	char *equals;

	if (!argv[1])
	{
		i = 0;
		while ((*g_env_copy)[i])
		{
			ft_putstr_fd("declare -x ", 1);
			ft_putendl_fd((*g_env_copy)[i], 1);
			i++;
		}
		return (0);
	}

	i = 1;
	while (argv[i])
	{
		equals = strchr(argv[i], '=');
		if (equals)
		{
			if (!is_valid_identifier(argv[i]))
			{
				write(2, "minishell: export: not a valid identifier\n", 40);
				return (1);
			}
			if (is_critical_var(argv[i]))
			{
				char *backup = ft_strdup_env(argv[i]);
				if (!backup)
					return (1);
				if (add_env_var(argv[i]))
				{
					free(backup);
					return (1);
				}
				free(backup);
			}
			else if (add_env_var(argv[i]))
				return (1);
		}
		i++;
	}
	return (0);
}
