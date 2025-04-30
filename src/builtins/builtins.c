/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaltayeh <yaltayeh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/04 20:57:28 by mkurkar           #+#    #+#             */
/*   Updated: 2025/04/30 21:21:43 by yaltayeh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	check_builtin(const char *cmd)
{
	if (!cmd)
		return (0);
	if (ft_strcmp(cmd, "cd") == 0
		|| ft_strcmp(cmd, "exit") == 0
		|| ft_strcmp(cmd, "export") == 0
		|| ft_strcmp(cmd, "unset") == 0
		|| ft_strcmp(cmd, "echo") == 0
		|| ft_strcmp(cmd, "pwd") == 0
		|| ft_strcmp(cmd, "env") == 0)
	{
		return (1);
	}
	return (0);
}

/*
* Regular built-ins can run in child process (output only)
* Shell built-ins must run in parent process (modify shell state)
*/
int	is_builtin(t_mini *mini, const char *cmd, int expand)
{
	int		test;
	t_list	*lst;

	if (!cmd)
		return (0);
	if (expand)
	{
		lst = expand_tokens_2lst(mini, cmd);
		if (!lst)
			return (-1);
		if (!lst->str)
		{
			lst_clean(&lst);
			return (0);
		}
		test = check_builtin(lst->str);
		lst_clean(&lst);
	}
	else
		test = check_builtin(cmd);
	return (test);
}

int	handle_builtin(t_mini *mini, char **argv, int _exit)
{
	int		err;

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
	g_sig = 0;
	if (_exit)
	{
		mini_clean(mini);
		exit(err);
	}
	return (err);
}
