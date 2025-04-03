/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_full_path.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaltayeh <yaltayeh@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/17 21:33:51 by yaltayeh          #+#    #+#             */
/*   Updated: 2025/03/22 14:54:28 by yaltayeh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
# define __USE_XOPEN
#include <sys/stat.h>

static int	search_command_path(char full_path[PATH_MAX], char *cmd)
{
	char	*path_env;
	char	*path;
	
	if (ft_strncmp(cmd, "/", 1) == 0
		|| ft_strncmp(cmd, "./", 2) == 0 
		|| ft_strncmp(cmd, "../", 3) == 0)
	{
		if (ft_strlcpy(full_path, cmd, PATH_MAX) >= PATH_MAX)
		{
			errno = ENAMETOOLONG;
			return (-1);
		}
		return (0);
	}
	path_env = ft_getenv("PATH");
	if (!path_env)
		return (-1);
	path = ft_strtok(path_env, ":");
	while (path)
	{
		if (snprintf(full_path, PATH_MAX, "%s/%s", path, cmd) < PATH_MAX \
				&& access(full_path, X_OK) == 0)
		// if (ft_strlcpy(full_path, path, PATH_MAX) < PATH_MAX
		// 	&& ft_strlcat(full_path, "/", PATH_MAX) < PATH_MAX
		// 	&& ft_strlcat(full_path, cmd, PATH_MAX) < PATH_MAX
		// 	&& access(full_path, X_OK) == 0)
			{
				free(path_env);
				return (0);
			}
		path = ft_strtok(NULL, ":");
	}
	free(path_env);
	return (1);
}

int check_permission(char full_path[PATH_MAX])
{
	// struct stat buf;

	// if (stat(full_path, &buf) == -1)
	// {
	// 	PRINT_SYSCALL_ERROR;
	// 	return (1);
	// }
	// if (buf.st_mode & S_IFDIR)
	// 	return (1);
	(void)full_path;
	return (0);
}

int	get_full_path(char full_path[PATH_MAX], char *cmd)
{
	int	err;

	err = search_command_path(full_path, cmd);
	if (err == -1)
	{
		PRINT_SYSCALL_ERROR;
		return (1);
	}
	if (err == 1)
	{
		ft_fprintf(2, PREFIX"%s: command not found\n", cmd);
		return (127);
	}
	return (check_permission(full_path));
}