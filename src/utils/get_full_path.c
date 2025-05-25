/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_full_path.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaltayeh <yaltayeh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/17 21:33:51 by yaltayeh          #+#    #+#             */
/*   Updated: 2025/05/25 17:32:32 by yaltayeh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <sys/stat.h>

static int	search_command_path(t_list *env,
							char full_path[PATH_MAX], char *cmd)
{
	char	*path_env;
	char	*path;

	path_env = ft_getenv(env, "PATH");
	if (!path_env && errno == ENOMEM)
		return (-1);
	if (!path_env)
		return (1);
	path = ft_strtok(path_env, ":");
	while (path)
	{
		if (ft_snprintf(full_path, PATH_MAX, "%s/%s", path, cmd) < PATH_MAX
			&& access(full_path, X_OK) == 0)
		{
			free(path_env);
			return (0);
		}
		path = ft_strtok(NULL, ":");
	}
	free(path_env);
	return (1);
}

static int	check_permission(char full_path[PATH_MAX])
{
	struct stat	buf;

	if (stat(full_path, &buf) == 0)
	{
		if (S_ISDIR(buf.st_mode))
			ft_fprintf(2, PREFIX"%s: Is a directory\n", full_path);
		else
			return (0);
		return (126);
	}
	return (1);
}

int	get_full_path(t_list *env, char full_path[PATH_MAX], char *cmd)
{
	int	err;

	if (ft_strlcpy(full_path, cmd, PATH_MAX) >= PATH_MAX)
	{
		errno = ENAMETOOLONG;
		return (1);
	}
	if (ft_strncmp(cmd, "/", 1) == 0
		|| ft_strncmp(cmd, "./", 2) == 0
		|| ft_strncmp(cmd, "../", 3) == 0)
		return (check_permission(full_path));
	err = search_command_path(env, full_path, cmd);
	if (err == -1)
		return (1);
	if (err == 1)
	{
		ft_fprintf(2, PREFIX"%s: command not found\n", cmd);
		return (127);
	}
	return (0);
}
