/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_full_path.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaltayeh <yaltayeh@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/17 21:33:51 by yaltayeh          #+#    #+#             */
/*   Updated: 2025/03/21 12:39:39 by yaltayeh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	check_exist(char *full_path, char *command)
{
	if (ft_strlcpy(full_path, command, PATH_MAX) >= PATH_MAX)
	{
		ft_fprintf(2, PREFIX"%s: command is too long\n", command);
		return (-1);
	}
	if (access(full_path, F_OK) != 0)
		return (0);
	if (ft_strncmp(full_path, "./", 2) == 0 \
		|| ft_strncmp(full_path, "/", 1) == 0)
	{
		if (access(full_path, F_OK) != 0)
		{
			ft_fprintf(2, PREFIX"%s: %s\n", full_path, strerror(errno));
			return (-127);
		}
		if (access(full_path, X_OK) == 0)
			return (1);
		ft_fprintf(2, PREFIX"%s: %s\n", full_path, strerror(errno));
		return (-126);
	}
	return (0);
}

static int	get_command_full_path(char *full_path, const char *command)
{
	char	*path_env;
	char	*token;

	path_env = ft_getenv("PATH");
	if (!path_env)
		return (-1);
	token = ft_strtok(path_env, ":");
	while (token)
	{
		if (ft_join_path(full_path, token, command) < PATH_MAX \
					&& access(full_path, X_OK) == 0)
		{
			free(path_env);
			return (1);
		}
		token = ft_strtok(NULL, ":");
	}
	free(path_env);
	return (0);
}

int	get_full_path(char *full_path, char **argv, char *command)
{
	int	err;

	if (!argv[0])
	{
		ft_fprintf(2, PREFIX"%s: command not found\n", command);
		return (126);
	}
	err = check_exist(full_path, argv[0]);
	if (err == 1)
		return (0);
	if (err < 0)
		return (-err);
	err = get_command_full_path(full_path, argv[0]);
	if (err == -1)
	{
		ft_fprintf(2, PREFIX"%s: %s\n", command, strerror(errno));
		return (1);
	}
	if (err == 1)
		return (0);
	ft_fprintf(2, PREFIX"%s: command not found\n", argv[0]);
	return (127);
}
