/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaltayeh <yaltayeh@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/04 20:57:28 by mkurkar           #+#    #+#             */
/*   Updated: 2025/04/14 06:21:39 by yaltayeh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
* Regular built-ins can run in child process (output only)
* Shell built-ins must run in parent process (modify shell state)
*/
int	is_builtin(t_list *env, char *cmd)
{
	if (!cmd)
		return (0);
	cmd = expand_str(env, cmd);
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

int	handle_builtin(t_mini *mini, char **argv, int _exit)
{
	int		err;

	if (!argv || !*argv)
		return (1);
	err = 1;
	if (ft_strcmp(*argv, "cd") == 0)
		err = ft_cd(mini, argv);
	else if (ft_strcmp(*argv, "exit") == 0)
		err = ft_exit(argv, &_exit);
	else if (ft_strcmp(*argv, "export") == 0)
		err = ft_export(mini, argv);
	else if (ft_strcmp(*argv, "unset") == 0)
		err = ft_unset(mini, argv);
	else if (ft_strcmp(*argv, "echo") == 0)
		err = ft_echo(argv);
	else if (ft_strcmp(*argv, "pwd") == 0)
		err = ft_pwd(argv);
	else if (ft_strcmp(*argv, "env") == 0)
		err = ft_env(mini, argv);
	free_dptr(argv);
	if (_exit)
		exit(err);
	return (err);
}
