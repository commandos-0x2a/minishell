/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkurkar <mkurkar@student.42amman.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/04 20:57:28 by mkurkar           #+#    #+#             */
/*   Updated: 2025/02/10 21:26:05 by mkurkar          ###   ########.fr       */
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
	if (ft_strcmp(cmd, "cd") == 0 || \
		ft_strcmp(cmd, "exit") == 0 || \
		ft_strcmp(cmd, "export") == 0 || \
		ft_strcmp(cmd, "unset") == 0)
		return (1);
	if (ft_strcmp(cmd, "echo") == 0 || \
		ft_strcmp(cmd, "pwd") == 0 || \
		ft_strcmp(cmd, "env") == 0)
		return (2);
	return (0);
}

int	handle_builtin(t_tokens *tok, char **argv, int _exit)
{
	int	ret;

	if (!*argv)
		return (1);
	ret = 1;
	if (ft_strcmp(*argv, "cd") == 0)
		ret = ft_cd(argv);
	else if (ft_strcmp(*argv, "exit") == 0)
		ret = ft_exit(argv, &_exit);
	else if (ft_strcmp(*argv, "export") == 0)
		ret = ft_export(argv);
	else if (ft_strcmp(*argv, "unset") == 0)
		ret = ft_unset(argv);
	else if (ft_strcmp(*argv, "echo") == 0)
		ret = ft_echo(argv);
	else if (ft_strcmp(*argv, "pwd") == 0)
		ret = ft_pwd(argv);
	else if (ft_strcmp(*argv, "env") == 0)
		ret = ft_env(argv);
	else
		return (1);
	if (_exit)
	{
		free_tokens(tok);
		exit(ret);
	}
	return (ret);
}
