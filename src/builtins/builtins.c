/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaltayeh <yaltayeh@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/04 20:57:28 by mkurkar           #+#    #+#             */
/*   Updated: 2025/04/03 23:26:36 by yaltayeh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
* Regular built-ins can run in child process (output only)
* Shell built-ins must run in parent process (modify shell state)
*/
int	is_builtin(char *cmd)
{
	if (!cmd)
		return (0);
	cmd = expand_str(cmd);
	if (!cmd)
		return (-1);
	if (ft_strcmp(cmd, "cd") == 0 || \
		ft_strcmp(cmd, "exit") == 0 || \
		ft_strcmp(cmd, "export") == 0 || \
		ft_strcmp(cmd, "unset") == 0 ||	\
		ft_strcmp(cmd, "echo") == 0 || \
		ft_strcmp(cmd, "pwd") == 0 || \
		ft_strcmp(cmd, "env") == 0)
		{
			free(cmd);
			return (1);
		}
	free(cmd);
	return (0);
}

int	handle_builtin(t_mdata *mdata, char **argv, int _exit)
{
	int		err;
	char	**expand_argv;

	if (!argv || !*argv)
		return (1);
	expand_argv = argv_expander2(argv, 0);
	free_dptr(argv);
	if (!expand_argv)
		return (1);
	err = 1;
	if (ft_strcmp(*expand_argv, "cd") == 0)
		err = ft_cd(expand_argv);
	else if (ft_strcmp(*expand_argv, "exit") == 0)
		err = ft_exit(expand_argv, &_exit);
	else if (ft_strcmp(*expand_argv, "export") == 0)
		err = ft_export(expand_argv);
	else if (ft_strcmp(*expand_argv, "unset") == 0)
		err = ft_unset(expand_argv);
	else if (ft_strcmp(*expand_argv, "echo") == 0)
		err = ft_echo(expand_argv);
	else if (ft_strcmp(*expand_argv, "pwd") == 0)
		err = ft_pwd(expand_argv);
	else if (ft_strcmp(*expand_argv, "env") == 0)
		err = ft_env(expand_argv);
	free_dptr(expand_argv);
	if (_exit)
		clean_and_exit(mdata, err);
	return (err);
}
