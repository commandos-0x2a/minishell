/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_simple_command.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaltayeh <yaltayeh@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/21 21:59:26 by yaltayeh          #+#    #+#             */
/*   Updated: 2025/04/19 12:11:52 by yaltayeh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "minishell.h"

static int	stop_process()
{
	if (g_sig != 0)
		return (-1);
	if (kill(getpid(), SIGSTOP) == -1)
		return (-1);
	if (g_sig != 0)
		return (-1);
	reset_signals();
	return (0);
}

void	execute_simple_command(t_mini *mini)
{
	char	**argv;
	char	full_path[PATH_MAX];
	int		err;

	if (stop_process() != 0)
		return ;
	if (is_subshell(mini->tokens))
		run_subshell(mini);
	if (expand_tokens(mini, mini->tokens) != 0)
		return ;
	argv = lst_2_argv(&mini->tokens);
	if (!argv)
		return ;
	if (is_builtin(mini, argv[0], 0))
		handle_builtin(mini, argv, 1);
	err = get_full_path(mini->env, full_path, argv[0]);
	if (err == 0)
	{
		execve(full_path, argv, lst_2_dptr(mini->env));
		err = 1;
	}
	free_dptr(argv);
	mini_clean(mini);
	exit(err);
}
