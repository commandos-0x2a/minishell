/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkurkar <mkurkar@student.42amman.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/11 12:00:00 by mkurkar           #+#    #+#             */
/*   Updated: 2025/01/10 20:02:02 by mkurkar          ###   ########.fr       */
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
	extern char **environ;
	int i;
	char *name;
	char *equals;
	int name_len;

	equals = strchr(var, '=');
	if (!equals)
		return (0);

	name_len = equals - var;
	name = malloc(name_len + 1);
	if (!name)
		return (1);
	strncpy(name, var, name_len);
	name[name_len] = '\0';

	i = 0;
	while (environ[i])
	{
		if (strncmp(environ[i], name, name_len) == 0 &&
			(environ[i][name_len] == '=' || environ[i][name_len] == '\0'))
		{
			free(environ[i]);
			environ[i] = ft_strdup_env(var);
			free(name);
			return (environ[i] ? 0 : 1);
		}
		i++;
	}
	free(name);
	return (2); // Variable not found
}

static int add_env_var(char *var)
{
	extern char **environ;
	char **new_environ;
	int i, result;

	result = update_env_var(var);
	if (result != 2) // 2 means variable not found
		return (result);

	if (!environ)
	{
		new_environ = malloc(sizeof(char *) * 2);
		if (!new_environ)
			return (1);
		new_environ[0] = ft_strdup_env(var);
		if (!new_environ[0])
		{
			free(new_environ);
			return (1);
		}
		new_environ[1] = NULL;
		environ = new_environ;
		return (0);
	}

	i = 0;
	while (environ[i])
		i++;
	new_environ = malloc(sizeof(char *) * (i + 2));
	if (!new_environ)
		return (1);

	i = 0;
	while (environ[i])
	{
		new_environ[i] = environ[i];
		i++;
	}
	new_environ[i] = ft_strdup_env(var);
	if (!new_environ[i])
	{
		free(new_environ);
		return (1);
	}
	new_environ[i + 1] = NULL;
	environ = new_environ;
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
	extern char **environ;
	int i;
	char *equals;

	if (!argv[1])
	{
		i = 0;
		while (environ[i])
		{
			write(1, "declare -x ", 11);
			write(1, environ[i], strlen(environ[i]));
			write(1, "\n", 1);
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
