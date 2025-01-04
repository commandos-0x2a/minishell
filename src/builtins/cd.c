/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkurkar <mkurkar@student.42amman.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/04 20:57:32 by mkurkar           #+#    #+#             */
/*   Updated: 2025/01/04 20:57:32 by mkurkar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_cd(char **argv)
{
	char	*path;
	char	cwd[PATH_MAX];

	if (!argv[1])
	{
		path = ft_getenv("HOME");
		if (!path)
		{
			ft_fprintf(2, "minishell: cd: HOME not set\n");
			return (1);
		}
	}
	else
		path = argv[1];

	if (chdir(path) == -1)
	{
		ft_fprintf(2, "minishell: cd: %s: %s\n", path, strerror(errno));
		return (1);
	}

	if (getcwd(cwd, sizeof(cwd)) == NULL)
	{
		ft_fprintf(2, "minishell: cd: %s\n", strerror(errno));
		return (1);
	}

	return (0);
}
