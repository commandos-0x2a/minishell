/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkurkar <mkurkar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/04 20:57:32 by mkurkar           #+#    #+#             */
/*   Updated: 2025/05/28 19:45:22 by mkurkar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*get_current_dir(void)
{
	char	cwd[PATH_MAX];

	if (getcwd(cwd, sizeof(cwd)) == NULL)
		ft_strlcpy(cwd, "~", sizeof(cwd));
	cwd[PATH_MAX - 1] = '\0';
	return (ft_strdup(cwd));
}

static int	handle_cd_path(t_mini *mini, char **argv, char **path)
{
	if (!argv[1])
	{
		*path = ft_getenv(mini->env, "HOME");
		if (!*path)
		{
			ft_fprintf(2, PREFIX"cd: HOME not set\n");
			return (1);
		}
	}
	else
		*path = argv[1];
	return (0);
}

static int	update_oldpwd(t_mini *mini)
{
	char	*old_pwd;
	char	*current_dir;
	int		ret;

	current_dir = get_current_dir();
	if (!current_dir)
	{
		ft_fprintf(2, PREFIX"cd: PWD not set\n");
		return (1);
	}
	old_pwd = ft_strjoin(2, "OLDPWD=", current_dir);
	free(current_dir);
	if (!old_pwd)
	{
		ft_fprintf(2, PREFIX"cd: memory allocation error\n");
		return (1);
	}
	ret = update_env(&mini->env, old_pwd);
	free(old_pwd);
	return (ret);
}

static int	update_pwd(t_mini *mini)
{
	char	*pwd;
	char	*current_dir;
	int		ret;

	current_dir = get_current_dir();
	if (!current_dir)
		return (1);
	pwd = ft_strjoin(2, "PWD=", current_dir);
	free(current_dir);
	if (!pwd)
	{
		ft_fprintf(2, PREFIX"cd: memory allocation error\n");
		return (1);
	}
	ret = update_env(&mini->env, pwd);
	free(pwd);
	return (ret);
}

int	ft_cd(t_mini *mini, char **argv)
{
	char	*path;

	if (update_oldpwd(mini) != 0)
		return (1);
	if (handle_cd_path(mini, argv, &path) != 0)
		return (1);
	if (chdir(path) == -1)
	{
		ft_fprintf(2, PREFIX"cd: %s: %s\n", path, strerror(errno));
		return (1);
	}
	if (update_pwd(mini) != 0)
		return (1);
	return (0);
}
